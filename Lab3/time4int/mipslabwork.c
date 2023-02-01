/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;
int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

volatile int* TE = (volatile int*) 0xbf886100;
volatile int* PE = (volatile int*) 0xbf886110;

int timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr( void )
{
  if(IFS(0) & 256){                //Bit 8 is the flag for interrupt
    timeoutcount++;
    IFSCLR(0) = 256;               //Clear flag in bit 8 
    if(timeoutcount == 10){    
      time2string( textstring, mytime );
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
      timeoutcount = 0;
    }
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  *TE = (*TE & 0xFF00);      //Set lower 8 bits to 0 (Set port e lower 8 bits to output(0))
  *PE = (*PE & 0x0);         //Set all bits to 0  (LEDS)
  TRISD = (TRISD | 0xFE0);   //Set MSB to 1 for bits 11-5 (inputs) 
  T2CON = 0x0;               //Stop the timer
  T2CONSET = 0x70;           // Set prescaling to max Decided by bits  
  TMR2 = 0x0;                //Reset the timer to 0
  PR2 = 31250;      //80mhz / 256 / 10
  IECSET(0) = 256;     //Enable interrupt timer 2 bit 8
  IPCSET(2) = 31;      //Priority and sub priority max
  enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  prime = nextprime (prime);
  display_string(0, itoaconv(prime));
  display_update();
}

