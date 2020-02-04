#ifndef _SPIJOYSTICK
#define _SPIJOYSTICK

void setCommand(unsigned char cmd, unsigned char param1, unsigned char param2, unsigned char param3, unsigned char param4, unsigned char *stdPktValues);

void getCommand(unsigned char cmd, unsigned char byteAmount, unsigned char *stdPktValues, unsigned char *rcvData);

unsigned char transfer(unsigned char bOut);

#endif


