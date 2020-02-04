#include "delay.h"
#include <generated/csr.h>

void delay(unsigned int ds)
{
	timer0_en_write(0);
	timer0_reload_write(0);
	timer0_load_write(CONFIG_CLOCK_FREQUENCY/CONFIG_CLOCK_FREQUENCY*ds);
	timer0_en_write(1);
	timer0_update_value_write(1);
	while(timer0_value_read()) timer0_update_value_write(1);
}

void delay_ms(unsigned int ds)
{
	delay(CONFIG_CLOCK_FREQUENCY/1000*ds);
}

void delay_us(unsigned int ds)
{
	delay(CONFIG_CLOCK_FREQUENCY/1000000*ds);
}
