/************************************************************************/
/*                                                                      */
/*		PmodJSTK2.h  --	PmodJSTK2 Command and Interface Functions		*/
/*                                                                      */
/************************************************************************/
/*	Author: 	James K. Colvin										    */
/*	Copyright:	2016, Digilent, Inc.									*/
/************************************************************************/
/*  File Description:                                                   */
/*                                                                      */
/*	This file contains the declarations and type definitions used for	*/
/*	accessing the PmodJSTK2.											*/
/*                                                                      */
/************************************************************************/
/*  Revision History:													*/
/*                                                                      */
/*	04/01/2016(MichaelA): created PC based application					*/
/*	04/25/2016(JamesC):	modified PC library for a Digilent MCU			*/
/*                                                                      */
/************************************************************************/

/* ------------------------------------------------------------ */
/*				Miscellaneous Declarations						*/
/* ------------------------------------------------------------ */

/* Define PmodJSTK2 SPI commands.
*/
#define mskCmd				0xFC

#define cmdSetLed			0x80
#define cmdSetLedOn			cmdSetLed | 0x01
#define cmdSetLedOff		cmdSetLed

#define cmdSetLedRGB		0x84

#define cmdSetInversion		0x88
#define cmdSetInversionX	0x88 | 0x02
#define cmdSetInversionY	0x88 | 0x01
#define cmdSetInversionOff	cmdSetInversion

#define cmdGetPosition		0xC0

#define cmdGetStatus		0xF0
#define cmdGetFirmwareVer	0xF1

#define cmdGetCalXMin		0xE0
#define cmdGetCalXMax		0xE1
#define cmdGetCalYMin		0xE2
#define cmdGetCalYMax		0xE3
#define cmdGetCalXCenMin	0xE4
#define cmdGetCalXCenMax	0xE5
#define cmdGetCalYCenMin	0xE6
#define cmdGetCalYCenMax	0xE7

#define cmdCalibrate		0xA4

#define cmdSetCalXMin		0xA8
#define cmdSetCalXMax		0xA9
#define cmdSetCalYMin		0xAA
#define cmdSetCalYMax		0xAB
#define cmdSetCalXCenMin	0xAC
#define cmdSetCalXCenMax	0xAD
#define cmdSetCalYCenMin	0xAE
#define cmdSetCalYCenMax	0xAF

#define cmdSetCalXMinMax	0xB0
#define cmdSetCalYMinMax	0xB1
#define cmdSetCalXCenMinMax	0xB2
#define cmdSetCalYCenMinMax	0xB3

#define cmdWriteFlash		0xB8
#define cmdRldFromFlash		0xBC

#define cbSndMax			16

/* Define the bit positions used in a status packet.
*/
#define bnCalibrating           7
#define bnLastCal               6
#define bnLastFWS               5
#define bnLastFRS               4
#define bnInvertX               1
#define bnInvertY               0

#define bitCalibrating          (1 << bnCalibrating)
#define bitLastCal              (1 << bnLastCal)
#define bitLastFWS              (1 << bnLastFWS)
#define bitLastFRS              (1 << bnLastFRS)
#define bitInvertX              (1 << bnInvertX)
#define bitInvertY              (1 << bnInvertY)

/* Define bit postiions used in fsButtons.
*/
#define bnExtpkt                7
#define bnTrigger               1
#define bnJstk                  0

#define bitExtpkt               (1 << bnExtpkt)
#define bitTrigger              (1 << bnTrigger)
#define bitJstk                 (1 << bnJstk)

/** defines that need to be supported* */
/*	Led States
*/
#define JSTK_LED1 0x01
#define JSTK_LED2 0x02

/*  Button States
*/
#define JSTK_BTN1 0x02
#define JSTK_BTN2 0x04
