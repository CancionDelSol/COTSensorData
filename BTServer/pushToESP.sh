SKETCH=./BTServer.ino
BOARD=esp32:esp32:esp32
PORT=/dev/ttyUSB1

#arduino-cli compile -b ${BOARD} ${SKETCH}
arduino-cli upload -b ${BOARD} -p ${PORT} ${SKETCH} 