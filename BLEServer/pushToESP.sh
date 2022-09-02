SKETCH=./BLEServer.ino
BOARD=esp32:esp32:esp32
PORT=/dev/ttyUSB1

echo "Compiling..."
arduino-cli compile -b ${BOARD} ${SKETCH}

echo "Uploading..."
arduino-cli upload -b ${BOARD} -p ${PORT} ${SKETCH}
