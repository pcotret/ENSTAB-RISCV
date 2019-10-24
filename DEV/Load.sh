
#!/bin/bash
export PATH =$PATH:/~riscV64/bin
echo 'export done'
echo '================================'
./buildNexys4ddr.py
echo 'buildNexys4ddr done'
echo '================================'
./Load.py
echo 'Load done'
echo '================================'
cd Firmware
make
echo 'make done'
echo '================================'
cd..
python3.7 litex/litex/tools/litex_term.py /dev/ttyUSB1 --kernel Firmware/Firmware.bin