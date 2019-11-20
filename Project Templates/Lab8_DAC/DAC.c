/*******************************************************************
 * DAC.c
 * Instructor: Gursel Serpen
 * Runs on TM4C123
 * Implementation of the 4-bit digital to analog converter
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Thomas Norris / Juliette Ulman
 * Section: 003
 * Date:    11/13/19
 *
 * Port B bits 5-2 have the 4-bit DAC
 *******************************************************************/

#include "DAC.h"
#include "../inc/tm4c123gh6pm.h"

// **************DAC_Init*********************
// Initialize 4-bit DAC outputs (PB2 - PB5)
// Initialize 1 bit debug output (PB0)
// Input: none
// Output: none
void DAC_Init(void){
	char PB = 0x02;
	char PBX_DIR = 0x3D;
	char PBX_DEN = 0x3D;
	char ZERO = 0x00;
	
	SYSCTL_RCGC2_R |= PB;
	
	while (!(SYSCTL_RCGC2_R & PB)) {
		// wait for clock to become active
	}
	
	// unlock, set directions and enable
	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTB_PCTL_R = ZERO;
	GPIO_PORTB_DIR_R |= PBX_DIR;
	GPIO_PORTB_DEN_R |= PBX_DEN;
}


// **************DAC_Out*********************
// output to DAC
// Input: 4-bit data, 0 to 15 
// Output: none
void DAC_Out(unsigned long data){
	// wave[] stores values from 0 - 15, PE0 to PE3
	// need to shift to output to PE2 - PE5
	data = data << 2;
	GPIO_PORTB_DATA_R = data;	
	
	// debug monitor, toggle PB0
	GPIO_PORTB_DATA_R ^= 0x01;
}
