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


#define WIDTH 128
#define HEIGHT 32

struct Snake snake;
struct Apple apple;
struct Apple apple2;
struct Apple apple3;

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
  
  T2CON = 0x0;        //Stop the timer
  T2CONSET = 0x8070;  // Set prescaling to max (bit 4-6) Bit 15 turns it on
  TMR2 = 0x0;         //Reset the timer to 0
  PR2 = 31250;        //80mhz / 256 / 10

  T1CON = 0x0;
  TMR1 = 0x0;         //Reset the timer to 0
  T1CONSET = 0x8070;  // Set prescaling to max (bit 4-6) Bit 15 turns it on
  PR2 = 312500;        //312 500KHz timer. PR = 312k Meaning 1000s a second

  gamedone = 0;  
  clear();
  border();

  //Snake init
	snake.x[0] = 16;
	snake.y[0] = 16;
	snake.length = 1;
	snake.direction = 1;
  
  //Apple init
  apple.x = 64;
  apple.y = 20; 
  drawpixel(apple.x, apple.y, 1);  
}

/*This function is called repetitively from the main program */
void gamemain( void )
{
  //timeoutcount = 0; //Reset timeoutcount in order to make pause and gameover less annoying
  if (getbtn4()) //Direction 3 means left
  {  
  T1CONSET = 0x0; //Turn off the timer 
  snake.direction = 3; 
  }

  if (getbtn3()) //Direction 1 means right
  { 
  T1CONSET = 0x0; //Turn off the timer 
  snake.direction = 1;
  }
  
  if (getbtn2())  //Up
  {
    T1CONSET = 0x0; //Turn off the timer 
    snake.direction = 2; 
  }

  if (getbtn1()) //Down
  {
    T1CONSET = 0x0; //Turn off the timer 
    snake.direction = 0;
  }

  if (getsw2()){        //Speed mode
     PR2 = 6125;        //80mhz / 256 = 5x faster
  } else {
    PR2 = 31250;
  }
  if(IFS(0) & 256){   //Bit 8 is the flag for interrupt
    timeoutcount++;
    IFSCLR(0) = 256;   //reset bit 8 in IFS0
  }
  if(timeoutcount == 2){
    moveSnake(&snake, &apple);
    display_image(0,display);
    timeoutcount = 0;
  }
}

void pause(){
    display_string(0, "     GAME");
	  display_string(1, "      IS");
	  display_string(2, "    PAUSED");
	  display_string(3, "");
	  display_update();
    while (getsw1() == 1){  //Keeps pause responsive without making screen flutter
      delay(200); 
    }
}
  
void gameoverfunc(){
  if (getsw4()){  //Instant restart mode
    gamedone = 0;
    gameinit();
  } else {
    display_string(0, "     GAME");
	  display_string(1, "     OVER");
	  display_string(2, "PRESS ANY BTN ");
	  display_string(3, " TO RESTART");
	  display_update();
    while (getbtns() == 0x0 && getbtn1 == 0x0){   //Keeps gameover responsive without making screen flutter
        delay(200);  
    } 
    gamedone = 0;
    gameinit();
  }
  
}  



// Functions -----------
