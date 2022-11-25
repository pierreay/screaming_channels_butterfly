#!/bin/zsh
SERIAL_PORT="/dev/ttyACM0"
echo "SERIAL_PORT=$SERIAL_PORT"
whadup && read "?Please, press RESET button to put dongle in bootloader mode. Continue?" \
    && make && make send "SERIAL_PORT=$SERIAL_PORT"
