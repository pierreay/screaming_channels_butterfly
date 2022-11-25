#!/bin/zsh
if [[ $# == 1 ]]; then
    SERIAL_PORT="$1"
else
    SERIAL_PORT="/dev/ttyACM0"
fi
echo "SERIAL_PORT=$SERIAL_PORT"
whadup && read "?Please, press RESET button to put dongle in bootloader mode. Continue?" \
    && make && make send "SERIAL_PORT=$SERIAL_PORT"
