#!/bin/zsh

# * Configuration

# In the /opt/nrf5-sdk/components/toolchain/gcc/Makefile.posix file on Arch
# Linux, configure the following:
# GNU_INSTALL_ROOT ?= /usr/bin/
# GNU_PREFIX ?= arm-none-eabi

# * Arguments

OPTIND=1
CLEAN_ENABLE=0
FLASH_ENABLE=0
SER_PORT="/dev/ttyACM0"
SDK_ROOT="/opt/nrf5-sdk"

# Program's help.
function help() {
    cat << EOF
Usage: run.sh [-c] [-f] [-p SERIAL_PORT] [-s SDK_ROOT]

Wrapper script around the original Makefile.

-c is to perform a clean of the build directory for fresh compilation (prevent errors) [default = False].
-f is to perform the flash after the compilation [default = False].
-p SERIAL_PORT is the serial port of the nRF52 dongle (search with whadup) [default = /dev/ttyACM0].
-s SDK_ROOT is the installation directory of the Nordic SDK [default = /opt/nrf5-sdk].
EOF
    exit 0
}

# Process args.
while getopts "h?cfp:s:" opt; do
  case "$opt" in
    h|\?)
      help
      ;;
    c) CLEAN_ENABLE=1
       ;;
    f) FLASH_ENABLE=1
       ;;
    p) SER_PORT=$OPTARG
      ;;
    s) SDK_ROOT=$OPTARG
      ;;
  esac
done

# Get rid of all arguments processed by getopts.
shift $((OPTIND-1))
# Skip the "--" keyword indicating that the following is a custom input.
[ "${1:-}" = "--" ] && shift

# * Script

set -e

if [[ $CLEAN_ENABLE -eq 1 ]]; then
    echo "[+] Clean build directory"
    rm -rf build
fi

echo "[+] Start compilation..."
make "SDK_ROOT=$SDK_ROOT"

if [[ $FLASH_ENABLE -eq 1 ]]; then
    echo "[+] Discover devices..."
    whadup
    read "?[?] Please, press RESET button to put dongle in bootloader mode. Continue?"
    
    echo "[+] Start flash..."
    make send "SERIAL_PORT=$SER_PORT" "SDK_ROOT=$SDK_ROOT"
else
    echo "[!] Skip flash!"
fi
