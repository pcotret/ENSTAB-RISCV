#include "display.h"
#include "delay.h"
#include <generated/csr.h>

void display(char motifs[8]) {
	display_dig_0_write(motifs[7]);
	display_dig_1_write(motifs[6]);
	display_dig_2_write(motifs[5]);
	display_dig_3_write(motifs[4]);
	display_dig_4_write(motifs[3]);
	display_dig_5_write(motifs[2]);
	display_dig_6_write(motifs[1]);
	display_dig_7_write(motifs[0]);
}
