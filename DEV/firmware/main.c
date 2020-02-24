#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <irq.h>
#include <uart.h>
#include <console.h>
#include <generated/csr.h>

#include "delay.h"
#include "spijoystick.h"
#include "display.h"
#include "PmodJSTK2.h"
#include "snake.h"

static void busy_wait(unsigned int ds)
{
	timer0_en_write(0);
	timer0_reload_write(0);
	timer0_load_write(CONFIG_CLOCK_FREQUENCY/10*ds);
	timer0_en_write(1);
	timer0_update_value_write(1);
	while(timer0_value_read()) timer0_update_value_write(1);
}

static char *readstr(void)
{
	char c[2];
	static char s[64];
	static int ptr = 0;

	if(readchar_nonblock()) {
		c[0] = readchar();
		c[1] = 0;
		switch(c[0]) {
			case 0x7f:
			case 0x08:
				if(ptr > 0) {
					ptr--;
					putsnonl("\x08 \x08");
				}
				break;
			case 0x07:
				break;
			case '\r':
			case '\n':
				s[ptr] = 0x00;
				putsnonl("\n");
				ptr = 0;
				return s;
			default:
				if(ptr >= (sizeof(s) - 1))
					break;
				putsnonl(c);
				s[ptr] = c[0];
				ptr++;
				break;
		}
	}
	return NULL;
}

static char *get_token(char **str)
{
	char *c, *d;

	c = (char *)strchr(*str, ' ');
	if(c == NULL) {
		d = *str;
		*str = *str+strlen(*str);
		return d;
	}
	*c = 0;
	d = *str;
	*str = c+1;
	return d;
}

static void prompt(void)
{
	printf("RUNTIME>");
}

static void help(void)
{
	puts("Available commands:");
	puts("help                            - this command");
	puts("reboot                          - reboot CPU");
	puts("display                         - display test");
	puts("led                             - led test");
	puts("knight                          - knight rider");
	puts("switch                          - switch test");
	puts("rgbled                          - rgb led test");
	puts("joystick                        - joystick test");
	puts("snake                           - snake onboard game");
	puts("vga                             - vga test");
}

static void reboot(void)
{
	ctrl_reset_write(1);
}

static void display_test(void)
{
	int i;
	signed char defill = 0;	//1->left, -1->right, 0->.
	
	char txtToDisplay[34] = {0, display_E, display_N, display_S, display_T, display_A, display_TR, display_B, display_R, display_E, display_T, display_A, display_G, display_N, display_E, 0, 0, 0, display_R, display_I, display_S, display_C, display_V, display_UR, display_P, display_R, display_O, display_J, display_E, display_C, display_T|display_DP, 0, 0, 0};
	
	while(!(buttons_in_read()&1)) {
		display(txtToDisplay);
		if(buttons_in_read()&(1<<3)) defill = ((defill<=-1) ? -1 : defill-1);
		if(buttons_in_read()&(1<<4)) defill = ((defill>=1) ? 1 : defill+1);
		if (defill > 0) {
			char tmp = txtToDisplay[0];
			for(i=0; i<sizeof(txtToDisplay)/sizeof(txtToDisplay[i]); i++) {
				txtToDisplay[i] = ((i==sizeof(txtToDisplay)/sizeof(txtToDisplay[i])-1) ? tmp : txtToDisplay[i+1]);
			}
		}
		else if(defill < 0) {
			char tmp = txtToDisplay[sizeof(txtToDisplay)/sizeof(txtToDisplay[0])-1];
			for(i=sizeof(txtToDisplay)/sizeof(txtToDisplay[i])-1; i>=0; i--) {
				txtToDisplay[i] = ((i==0) ? tmp : txtToDisplay[i-1]);
			}
		}
		delay_ms(200);
	}
}

static void led_test(void)
{
	unsigned short i;
	printf("led_test...\n");
	for(i=0; i<32; i++) {
		leds_out_write(i);
		busy_wait(1);
	}
}

static void knight_rider(void)
{
	char i;
	unsigned short count=1;
	printf("knight_rider...\n");
	for(i=0; i<15; i++) {
		count=count*2;
		leds_out_write(count);
		busy_wait(1);
	}
	for(i=16; i>0; i--) {
		count=count/2;
		leds_out_write(count);
		busy_wait(1);
	}
}

static void switch_test(void)
{
	unsigned short temp = switchs_in_read();
	printf("switch_test...\n");
	printf("switch bus : %i\n", temp);
	leds_out_write(temp);
}

static void rgbled_test(void)
{
	/*unsigned int T = 128;
	unsigned int diviseur = 32;
	char intensity = 50;	//percentage
	char select = 0;	//1->left, 0->right
	unsigned int cpt_r=0, cpt_g=diviseur*1, cpt_b=diviseur*2;
	
	led16_r_period_write(T);
	led16_g_period_write(T);
	led16_b_period_write(T);
	
	led17_r_period_write(T);
	led17_g_period_write(T);
	led17_b_period_write(T);
	
	led16_r_enable_write(1);
	led16_g_enable_write(1);
	led16_b_enable_write(1);
	
	led17_r_enable_write(1);
	led17_g_enable_write(1);
	led17_b_enable_write(1);
		
	while(!(buttons_in_read()&1<<0)) {		//center
		if(buttons_in_read()&(1<<1)) {	//down
			if(intensity==0)intensity=0;
			else intensity -= 1;
		}
		if(buttons_in_read()&(1<<2)) {	//up
			if(intensity>=100)intensity=100;
			else intensity += 1;
		}
		if(buttons_in_read()&(1<<3)) select = 0;	//right
		if(buttons_in_read()&(1<<4)) select = 1;	//left
				
		if(select==0) {
			led17_r_width_write(0);
			led17_g_width_write(0);
			led17_b_width_write(0);
			
			if(cpt_r<diviseur) led16_r_width_write((float)cpt_r/diviseur*T*intensity/100);
			else if(cpt_r<2*diviseur) led16_r_width_write((2-(float)cpt_r/diviseur)*T*intensity/100);
			else led16_r_width_write(0);
			
			if(cpt_g<diviseur) led16_g_width_write((float)cpt_g/diviseur*T*intensity/100);
			else if(cpt_g<2*diviseur) led16_g_width_write((2-(float)cpt_g/diviseur)*T*intensity/100);
			else led16_g_width_write(0);
			
			if(cpt_b<diviseur) led16_b_width_write((float)cpt_b/diviseur*T*intensity/100);
			else if(cpt_b<2*diviseur) led16_b_width_write((2-(float)cpt_b/diviseur)*T*intensity/100);
			else led16_b_width_write(0);
		}
		else {
			led16_r_width_write(0);
			led16_g_width_write(0);
			led16_b_width_write(0);
			
			if(cpt_r<diviseur) led17_r_width_write((float)cpt_r/diviseur*T*intensity/100);
			else if(cpt_r<2*diviseur) led17_r_width_write((2-(float)cpt_r/diviseur)*T*intensity/100);
			else led17_r_width_write(0);
			
			if(cpt_g<diviseur) led17_g_width_write((float)cpt_g/diviseur*T*intensity/100);
			else if(cpt_g<2*diviseur) led17_g_width_write((2-(float)cpt_g/diviseur)*T*intensity/100);
			else led17_g_width_write(0);
			
			if(cpt_b<diviseur) led17_b_width_write((float)cpt_b/diviseur*T*intensity/100);
			else if(cpt_b<2*diviseur) led17_b_width_write((2-(float)cpt_b/diviseur)*T*intensity/100);
			else led17_b_width_write(0);
		}
		
		cpt_r = (cpt_r+1)%(3*diviseur);
		cpt_g = (cpt_g+1)%(3*diviseur);
		cpt_b = (cpt_b+1)%(3*diviseur);
		
		busy_wait(1);
	}
	led16_r_width_write(0);
	led16_g_width_write(0);
	led16_b_width_write(0);
	led17_r_width_write(0);
	led17_g_width_write(0);
	led17_b_width_write(0);
	*/
}

static void joystick_test(void)
{
	unsigned short smpX,smpY;
	unsigned char fsButtons=0;
	unsigned char stdPktValues [5];
	unsigned char rtrnValues [2];
	unsigned char x,y;
	unsigned short i = 1;
	while((fsButtons&bitJstk)==0) {
		getCommand(cmdGetPosition,2,stdPktValues,rtrnValues);
		smpX = stdPktValues[0]+(stdPktValues[1]<<8);
		smpY = stdPktValues[2]+(stdPktValues[3]<<8);
		fsButtons = stdPktValues[4];
		x = rtrnValues[0];
		y = rtrnValues[1];
		if(x < 85) i = ((i>=0x8000) ? 0x8000 : i*2);
		else if(x > 170) i = ((i<=1) ? 1 : i/2);
		else i=i;
		leds_out_write(i);
		delay_ms(250);
	}
	leds_out_write(0);
}

static void vga_test(void)
{
	int x,y;
	
	for(y=0; y<480; y++) {
		for(x=0; x<640; x++) {
			vga_cntrl_mem_we_write(0);
			vga_cntrl_mem_adr_write(y*640+x);
			if(x<640/3)	vga_cntrl_mem_data_w_write(((int)(x/10)%2^(int)(y/10)%2)*15);
			else if(x<2*640/3) vga_cntrl_mem_data_w_write((((int)(x/10)%2^(int)(y/10)%2)*15)<<4);
			else vga_cntrl_mem_data_w_write((((int)(x/10)%2^(int)(y/10)%2)*15)<<8);
			vga_cntrl_mem_we_write(1);
		}
	}
}

static void console_service(void)
{
	char *str;
	char *token;

	str = readstr();
	if(str == NULL) return;
	token = get_token(&str);
	if(strcmp(token, "help") == 0)
		help();
	else if(strcmp(token, "reboot") == 0)
		reboot();
	else if(strcmp(token, "display") == 0)
		display_test();
	else if(strcmp(token, "led") == 0)
		led_test();
	else if(strcmp(token, "knight") == 0)
		knight_rider();
	else if(strcmp(token, "switch") == 0)
		switch_test();
	else if(strcmp(token, "rgbled") == 0)
		rgbled_test();
	else if(strcmp(token, "joystick") == 0)
		joystick_test();
	else if(strcmp(token, "snake") == 0)
		snake();
	else if(strcmp(token, "vga") == 0)
		vga_test();
	prompt();
}

int main(void)
{
	irq_setmask(0);
	irq_setie(1);
	uart_init();

	puts("\nRiscV project - CPU testing software built "__DATE__" "__TIME__"\n");
	help();
	prompt();

	while(1) {
		console_service();
	}

	return 0;
}
