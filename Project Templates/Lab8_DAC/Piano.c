/*******************************************************************
 * piano.c
 * Instructor: Gursel Serpen
 * Runs on TM4C123
 * There are four keys in the piano
 * Authors: Daniel Valvano,
 * 					Thomas Royko
 * Student: Thomas Norris / Juliette Ulman
 * Section: 003
 * Date:    11/13/19
 *
 * Port E bits 2-0 have 3 piano keys
 *******************************************************************/

#include "Piano.h"
#include "..//inc//tm4c123gh6pm.h"


// **************Piano_Init*********************
// Initialize piano key inputs (PE0 - PE2)
// Input: none
// Output: none
void Piano_Init(void){ 
	char PE = 0x10;
	char PEX_DIR = ~0x07;
	char PEX_DEN = 0x07;
	char PEX_PDR = 0x07;
	
	SYSCTL_RCGC2_R |= PE;
	
	while (!(SYSCTL_RCGC2_R & PE)) {
		// wait for clock to become active
	}
	
	// unlock, set directions and PDRs
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTE_PDR_R |= PEX_PDR;
	GPIO_PORTE_DIR_R &= PEX_DIR;
	GPIO_PORTE_DEN_R |= PEX_DEN;
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
