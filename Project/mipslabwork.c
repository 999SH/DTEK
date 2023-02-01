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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 128
#define HEIGHT 32

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

//volatile int* TE = (volatile int*) 0xbf886100;
//volatile int* PE = (volatile int*) 0xbf886110;

int timeoutcount = 0;


/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void gameinit( void )
{
  TRISE = TRISE & 0xFF00;
  PORTE = PORTE & 0x0;
  TRISD = (TRISD | 0xFE0);
  
  T2CON = 0x0;     //Stop the timer
  T2CONSET = 0x8070;  // Set prescaling to max
  TMR2 = 0x0;      //Reset the timer to 0
  PR2 = 31250;      //80mhz / 256 / 10

  /*struct Snake snake = {
  	.x = {64},
  	.y = {16},
  	.length = 1,
	  .direction = 1,
	};
 */
  return;
}

/*  getsw archive 
    mytime = (getsw() << 4 | mytime); 
    mytime = (getsw() << 12 | mytime); 
    mytime = (getsw() << 8 | mytime); */


/*
This function is called repetitively from the main program */
void gamemain( void )
{
  if (getbtn4()){  //1000 = button 4
  }

  if (getbtn3()){ //0100 = button 3
  }

  if (getbtn2())  //0010 = button 2
  {
  }


  if(IFS(0) & 256){   //Bit 8 is the flag for interrupt
    timeoutcount++;
    IFSCLR(0) = 256;   //reset bit 8 in IFS0
  }

 /*
  int loop;
  for (loop = 0; loop < 512; loop++) {
    moveSnake(&snake);
  }
*/
  if(timeoutcount == 10){
    //time2string( textstring, mytime );
    //display_string( 3, textstring );
    //display_update();
    //tick( &mytime );
    clear();
    display_image(0,display);
    PORTE = PORTE+1;
    delay ( 1000 );
    display_image(0,display);
    PORTE = PORTE+1;
    delay ( 1000 );
  }
}
 
  
  

// Functions -----------
