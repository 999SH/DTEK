/* main.c

   This file written 2015 by F Lundevall and David Broman

   Latest update 2015-09-15 by David Broman

   For copyright and licensing, see file COPYING */

#include <stddef.h>   /* Declarations of integer sizes and the like, part 1 */
#include <stdint.h>   /* Declarations of integer sizes and the like, part 2 */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

void saveinfo(char s[], void * a, size_t ns );
void showinfo(void);
void u32init(void);

int gv; /* Global variable. */
int in = 3; /* Global variable, initialized to 4711. */

void fun(int param)
{
  param++; //Increment int that is called in fun()
  saveword( "AF1: param", &param ); //Save the adress of Param
  gv = param; //set the global variable to the argument 
}

/* This is the main function */
int main()
{
  /* Local variables. */
  int m;  //Declare m, local variable in main
  int * p; /* Declare p as pointer, so that p can hold an address. */
  char cs[ 9 ] = "Bonjour!"; //Char array = charpointer
  char * cp = cs; /* Declare cp as pointer, initialise cp to point to cs */ //cp is the pointer for cs, altough cs is already a pointer

  /* Do some calculation. */
  gv = 4;  //Set global variable to 4
  m = gv + in; //m equals 4 + 3 = 7

  /* Check the addresses and values of some variables and stuff */
  saveword( "AM1: gv", &gv );
  saveword( "AM2: in", &in );
  saveword( "AM3: fun", &fun );
  saveword( "AM4: main", &main );

  p = &m; //set the pointer to the adress of m

  /* Check p and m */
  saveword( "AM5: p", &p );
  saveword( "AM6: m", &m );

  /* Change *p */

  *p = *p + 1;  //set the value of deref p to p+1. should be 8

  /* Check p and m */
  saveword( "AM7: p", &p );
  saveword( "AM8: m", &m );

  p = (int*)cp;   /* Casting a char pointer to an integer pointer */ 
                  //set P to char pointer cs, now int pointer?
  saveword( "AM9: p", &p );  //P should be same adress as cs[0]

  savebyte( "AM10: cs[0]", &cs[0] );
  savebyte( "AM11: cs[1]", &cs[1] );
  savebyte( "AM12: cs[2]", &cs[2] );
  savebyte( "AM13: cs[3]", &cs[3] );

  *p = 0x1234abcd; /* It starts to get interesting... */ //Stored as little endian which means cs0 stores cd

  savebyte( "AM14: cs[0]", &cs[0] );
  savebyte( "AM15: cs[1]", &cs[1] ); 
  savebyte( "AM16: cs[2]", &cs[2] );
  savebyte( "AM17: cs[3]", &cs[3] );

  fun(m); //increment m, should be 9 in param, since we incremented p earlier. 
          //m does not change since it is a void function, which means a copy of m is created
          //gv does change since it is equal to the copy of m, which is param. 
    /* Re-check the addresses and values of m and gv */
  saveword( "AM18: m", &m );
  saveword( "AM19: gv", &gv );

  showinfo();
}
