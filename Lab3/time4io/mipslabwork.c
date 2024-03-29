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

char textstring[] = "text, more text, and even more text!";

volatile int* TE = (volatile int*) 0xbf886100;
volatile int* PE = (volatile int*) 0xbf886110;

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  *TE = (*TE & 0xFF00);
  *PE = (0x0);
  TRISD = (TRISD | 0xFE0);
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{

  if (0x4 & getbtns())
  {
    mytime = 0x0FFF & mytime;
    mytime = (getsw() << 12 | mytime); 
  }
  if (0x2 & getbtns())
  {
    mytime = 0xF0FF & mytime; 
    mytime = (getsw() << 8 | mytime); 
  }
  if (0x1 & getbtns())
  {
    mytime = 0xFF0F & mytime; 
    mytime = (getsw() << 4 | mytime); 
  }
 
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
  *PE = *PE+1;
  
  
  
  return;
}
