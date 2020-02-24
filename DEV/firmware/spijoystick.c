#include "spijoystick.h"
#include "delay.h"
#include <generated/csr.h>

void setCommand(unsigned char cmd, unsigned char param1, unsigned char param2, unsigned char param3, unsigned char param4, unsigned char *stdPktValues) {
	//collect all of the command parameters into a single array
	unsigned char cmdData [5] = {cmd, param1, param2, param3, param4};
	//varaible for "for loop"
    unsigned char i;
	
	//bring the chip select line low
	joystick_cs_write(0);
	//delay as appropriate
	delay_us(5);
	for(i=0; i<5; i++) {
		//delay as appropriate
		delay_us(10);
		//transfer
		stdPktValues[i] = transfer(cmdData[i]);
	}
	//bring the chip select line high
	joystick_cs_write(1);
	//delay as appropriate
	delay_us(25);
}

void getCommand(unsigned char cmd, unsigned char byteAmount, unsigned char *stdPktValues, unsigned char *rcvData) {
	//variable for "for loops"
    unsigned char i;
	
	//bring the chip select line low
	joystick_cs_write(0);
	//delay as appropriate
	delay_us(15);
	//get first standard packet value and send the command
	stdPktValues[0] = transfer(cmd);
	for(i=1; i<5; i++) {
		//delay as appropriate
		delay_us(10);
		//transfer
		stdPktValues[i] = transfer(0x00);
	}
	for(i=0; i<byteAmount; i++) {
		//delay as appropriate
		delay_us(10);
		//transfer
		rcvData[i] = transfer(0x00);
	}
	//bring the chip select line high
	joystick_cs_write(1);
	//delay as appropriate
	delay_us(25);
}

unsigned char transfer(unsigned char bOut) {
	unsigned char bit, bIn=0x00;
	
	for (bit = 0x80; bit; bit >>= 1) {
		// Shift-out a bit to the MOSI line
	    joystick_mosi_write((bOut & bit) ? 1 : 0);
	    
		// Delay for at least the peer's setup time
	    delay(50);

	    // Pull the clock line high
	    joystick_clk_write(1);

		// Shift-in a bit from the MISO line
	    if (joystick_miso_read() == 1)
	        bIn |= bit;
	        
	    // Delay for at least the peer's hold time
	    delay(50);

	    // Pull the clock line low
	    joystick_clk_write(0);
	}
	return bIn;
}
