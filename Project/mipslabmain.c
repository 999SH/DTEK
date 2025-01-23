/* mipslabmain.c

   This file written 2015 by Axel Isaksson,
   modified 2015, 2017 by F Lundevall

   Latest update 2017-04-21 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */


int main(void) {
        /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
	
	display_init();
	
	display_string(0, "Welcome");
	display_string(1, "to snake");
	display_string(2, "by Viktor");
	display_string(3, "Salomonsson!");
	display_update();

	delay( 5000 );
	

	display_string(0, "SW4 = I-RSTRT");
	display_string(1, "SW3 = FUN MODE");
	display_string(2, "SW2 = SUPERFAST ");
	display_string(3, "SW1 = PAUSE ");
	display_update();

	delay( 5000 );

	display_string(0, "BTN 4 = LEFT");
	display_string(1, "BTN 3 = RIGHT");
	display_string(2, "BTN 2 = DOWN");
	display_string(3, "BTN 1 = UP");
	display_update();

	delay( 5000 );
	

	gameinit(); /* Do any lab-specific initialization */


	while( 1 ) {
	    switch (getsw1()){
	    	case 0: 
	    	    gamemain();
	    	    break;
	    	case 1:
	    	    pause();
	    	    break;
	    }
	    switch (gamedone){
	        case 0:
		    gamemain();
		    break;
	    	case 1: 
		    gameoverfunc();
		    break;
	    }
	}
	
	return 0;
}
