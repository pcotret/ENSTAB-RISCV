#!/bin/bash

./load.py
echo 'Load done'
echo '================================'
cd Firmware
make all
make clean
echo 'make done'
echo '================================'
cd ..
python3 litex/litex/tools/litex_term.py /dev/ttyUSB1 --kernel Firmware/firmware.bin
