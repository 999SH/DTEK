#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int getsw( void )
{
    return ((PORTD >> 8) & 0xF);
}


int getsw4( void )
{
    return ((PORTD >> 8) & 0x8);
}

int getsw3( void )
{
    return ((PORTD >> 8) & 0x4);
}

int getsw2( void )
{
    return ((PORTD >> 8) & 0x2);
}

int getsw1( void )
{
    return ((PORTD >> 8) & 0x1);
}

int getbtns( void )
{
    return ((PORTD >> 5) & 0x7);
}


int getbtn4(void){
    return ((PORTD >> 5) & 0x4);
}

int getbtn3(void){
    return ((PORTD >> 5) & 0x2);
}

int getbtn2(void){
    return ((PORTD >> 5) & 0x1);
}

int getbtn1(void){
  return ((PORTF>>1) & 0x1)<<9;
}
