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

volatile int* portE = (volatile int*) 0xbf886110;// portE is used in multiple function, therefor global

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trisE = (volatile int*) 0xbf886100; // initialize trisE 

  *trisE = *trisE & 0xffffff00;  // set bits 7 - 0 to outputs
  *portE = 0;                   // turns of all the leds

  TRISD &= 0x0fe0;              // initialize port D, 11 - 5 as inputs
  
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  (*portE)++; // increment portE with  1
  display_image(96, icon);

  int btns = getbtns();
  if(btns){
    int sw = getsw();
    if(btns & 4){ // Button 4
      mytime = (mytime & 0x0fff);
      mytime = (sw << 12) | mytime;
    }
    if(btns & 2){ // Button 3
      mytime = (mytime & 0xf0ff);
      mytime = (sw << 8) | mytime ;
    }
    if(btns & 1){ // Button 2
      mytime = (mytime & 0xff0f);
      mytime = (sw << 4) | mytime;
    }
  }
}
