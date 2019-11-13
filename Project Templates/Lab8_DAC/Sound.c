/*******************************************************************
 * Sound.c
 * Instructor: Gursel Serpen
 * Runs on TM4C123
 * Use the SysTick timer to request interrupts at a particular period.
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Thomas Norris / Juliette Ulman
 * Section: 003
 * Date:    11/13/19
 *
 * This module calls the 4-bit DAC
 *******************************************************************/

#include <stdint.h>

#include "Sound.h"
#include "DAC.h"
#include "SysTickInts.h"
#include "..//inc//tm4c123gh6pm.h"

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void){
	SysTick_Init(16000); // change me
	DAC_Init();
}

// **************Sound_Tone*********************
// Change Systick periodic interrupts to start sound output
// This routine sets the RELOAD and starts SysTick
// Input: interrupt period
//           Units of period are 12.5ns
//           Maximum is 2^24-1
//           Minimum is determined by length of ISR
// Output: none
void Sound_Tone(unsigned long period){

}


// **************Sound_Off*********************
// Stop outputing to DAC
// This routine stops the sound output
// Output: none
void Sound_Off(void){
 
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void){
   char poop = 4;
}
