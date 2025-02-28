/*******************************************************************
 * piano.c
 * Instructor: ***fill this in***
 * Runs on TM4C123
 * There are four keys in the piano
 * Authors: Daniel Valvano,
 * 					Thomas Royko
 * Student: ***fill this in***
 * Section: ***fill this in***
 * Date:    ***fill this in***
 *
 * Port E bits 3-0 have 4 piano keys
 *******************************************************************/

#include "Piano.h"
#include "..//inc//tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs
// Input: none
// Output: none
void Piano_Init(void){ 
  
}

// **************Piano_In*********************
// Input from piano key inputs
// Input: none 
// Output: 0 to 15 depending on keys
// 0x01 is key 0 pressed, 0x02 is key 1 pressed,
// 0x04 is key 2 pressed, 0x08 is key 3 pressed
unsigned long Piano_In(void){
  
  return 0; // remove this, replace with input
}
