/*******************************************************************
 * Lab8.c
 * Instructor: Gursel Serpen
 * Runs on TM4C123
 * Use SysTick interrupts to implement a 4-key digital piano
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Thomas Norris / Juliette Ulman
 * Section: 003
 * Date:    11/13/19
 *
 * Port B bits 5-2 have the 4-bit DAC
 * Port E bits 2-0 have 3 piano keys
 *******************************************************************/

#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delayMs(unsigned long msec);
void Heartbeat_Init(void);
void Heartbeat_Run(void);

// Notes C, E, G
const int tone1Hz = 262;
const int tone2Hz = 330; 
const int tone3Hz = 392;

int main(void){
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
	// activate grader and set system clock to 80 MHz
	TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210, ScopeOn);

	// PortE used for piano keys, PortB used for DAC        
	Sound_Init(); // initialize SysTick timer and DAC
	Piano_Init(); // initialize piano key inputs
	Heartbeat_Init(); // initialize heartbeat
	EnableInterrupts();  // enable after all initialization are done
	
	while(1) {
		Heartbeat_Run();
		
		switch(Piano_In()) {
			case 0x01:
				Sound_Tone(tone1Hz);
				break;
			case 0x02:
				Sound_Tone(tone2Hz);
				break;
			case 0x04:
				Sound_Tone(tone3Hz);
				break;
			default:
				Sound_Off();
				break;
		}
	}
}

// PF2 as the heartbeat LED
void Heartbeat_Init(void) {
	char PF = 0x20;
	char PFX_DIR = 0x04;
	char PFX_DEN = 0x04;
	
	SYSCTL_RCGC2_R |= PF;
	
	while (!(SYSCTL_RCGC2_R & PF)) {
		// wait for clock to become active
	}
	
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTF_DIR_R |= PFX_DIR;
	GPIO_PORTF_DEN_R |= PFX_DEN;
}

void Heartbeat_Run(void) {
	delayMs(5);
	GPIO_PORTF_DATA_R ^= 0x04;
}

// software timer, delays number of ms supplied
void delayMs(unsigned long msec) { 
	unsigned long count;
	while(msec > 0 ) {  // repeat while there are still delay
		count = 16000;    // about 1ms
		while (count > 0) { 
			count--;
		} // This while loop takes approximately 3 cycles
		msec--;
	}
}
