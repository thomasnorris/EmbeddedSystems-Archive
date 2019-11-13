/*******************************************************************
 * piano.c
 * Instructor: Gursel Serpen
 * Runs on TM4C123
 * There are three keys in the piano
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

// Notes C, E, G
const int key0ToneHz = 262;
const int key1ToneHz = 330; 
const int key2ToneHz = 392;
	
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
	
	// unlock, set directions, PDRs, and enable
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTE_PDR_R |= PEX_PDR;
	GPIO_PORTE_DIR_R &= PEX_DIR;
	GPIO_PORTE_DEN_R |= PEX_DEN;
}

// **************Piano_In*********************
// Input from piano key inputs. Only one key will be pressed at a time
// Input: none 
// Output: 0x01, 0x02, or 0x04
// 0x01 is key 0, 0x02 is key 1,
// 0x04 is key 2
unsigned long Piano_In(void) {
	// todo: this
	if (GPIO_PORTE_DATA_R & 0x01)
		return 0x01;
	if (GPIO_PORTE_DATA_R & 0x02)
		return 0x02;
	if (GPIO_PORTE_DATA_R & 0x04)
		return 0x04;
	
	return 0;
}
