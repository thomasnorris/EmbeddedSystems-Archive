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

const int tableSize = 32;

const unsigned char wave[tableSize] = {
	8, 9, 11, 12, 13, 14, 14, 15, 
	15, 15, 14, 14, 13, 12, 11, 9, 
	8, 7, 5, 4, 3, 2, 2, 1, 1, 1, 
	2, 2, 3, 4, 5, 7
};
unsigned char currentIndex = 0;

// **************Sound_Init*********************
// Initialize Systick periodic interrupts
// Also calls DAC_Init() to initialize DAC
// Input: none
// Output: none
void Sound_Init(void) {
	Sound_Off();
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
void Sound_Tone(unsigned long toneHz) {
	unsigned long period = toneHz * tableSize;
	Sound_Off();
	SysTick_Init(period);
}


// **************Sound_Off*********************
// Stop outputing to DAC
// This routine stops the sound output
// Output: none
void Sound_Off(void) {
	SysTick_Init(0);
}


// Interrupt service routine
// Executed every 12.5ns*(period)
void SysTick_Handler(void) {
	// get the next index, loop to index 0 after going through all of them
	currentIndex = (currentIndex + 1) & 0x1F;
	DAC_Out(wave[currentIndex]);
}
