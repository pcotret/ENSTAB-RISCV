#include "snake.h"

#include <stdlib.h>
#include <stdio.h>

#include "spijoystick.h"
#include "PmodJSTK2.h"
#include "display.h"
#include "delay.h"

void snake(void) {
	unsigned char fsButtons=0;
	unsigned char stdPktValues [5];
	unsigned char rtrnValues [2];
	signed char x,y;
	
	char mvt=0, lastmvt=4;	//1-> up; 2->down; 3->left; 4->right
							//1->left; 2->right; 3->up; 4->down
	char seg = 0;
	char motif[8] = {0,0,0,0,0,0,0,0};
	
	int i, digit = 0;
	
	motif[digit] = ~(1<<seg);

	while((fsButtons&bitJstk)==0) {
		//setCommand(cmdSetInversionY,0,0,0,0,stdPktValues);
		//lecture joystick
		getCommand(cmdGetPosition,2,stdPktValues,rtrnValues);
		fsButtons = stdPktValues[4];
		x = rtrnValues[0]-128;
		y = rtrnValues[1]-128;
	
		//choix mvt
		if(85 <= (abs(x)|abs(y))) {
			//if(abs(x)>=abs(y)) mvt = ((x>0) ? ((mvt==3) ? 3 : 4) : ((mvt==4) ? 4 : 3));
			//else mvt = ((y>0) ? ((mvt==2) ? 2 : 1) : ((mvt==1) ? 1 : 2));
			if(abs(x)>=abs(y)) mvt = ((x>0) ? ((mvt==2) ? 2 : 1) : ((mvt==1) ? 1 : 2));
			else mvt = ((y>0) ? ((mvt==4) ? 4 : 3) : ((mvt==3) ? 3 : 4));
		
			//maj motif
			switch(mvt) {
				case 1:
					switch (seg) {
						case 2:	seg = 1;
							break;
						case 3:	seg = ((lastmvt == 3) ? 4 : ((lastmvt == 4) ? 2 : seg));
							break;
						case 4: seg = 5;
							break;
						case 6:	seg = ((lastmvt == 3) ? 5 : ((lastmvt == 4) ? 1 : seg));
							break;
						default: mvt=lastmvt;
					}
					break;
				case 2:
					switch (seg) {
						case 1:	seg = 2;
							break;
						case 0:	seg = ((lastmvt == 3) ? 5 : ((lastmvt == 4) ? 1 : seg));
							break;
						case 5: seg = 4;
							break;
						case 6:	seg = ((lastmvt == 3) ? 4 : ((lastmvt == 4) ? 2 : seg));
							break;
						default: mvt=lastmvt;
					}
					break;
				case 3: if ((seg != 1) && (seg != 2)) digit = ((digit == 0) ? 7 : digit-1);
				case 4:
					if ((mvt==4) && (seg != 4) && (seg !=5)) digit = ((digit == 7) ? 0 : digit+1);
					switch (seg) {
						case 1: 
						case 5:	seg = ((lastmvt == 2) ? 6 : ((lastmvt == 1) ? 0 : seg));
							break;
						case 2:
						case 4:	seg = ((lastmvt == 2) ? 3 : ((lastmvt == 1) ? 6 : seg));
							break;
					}
					break;
			}
		}
		
		for(i=0; i<8; i++) {
			motif[i] = ((i==digit) ? (1<<seg) : 0);
		}
		
		//affichage motif
		display(motif);
		
		delay_ms(200);
		
		lastmvt = mvt;
	}
	
	sprintf(motif,"%c%c%c%c%c%c%c%c",display_G, display_A, display_M, display_E, display_O, display_V, display_E, display_R);
	
	//affichage motif
	display(motif);
}
