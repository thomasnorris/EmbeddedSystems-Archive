/*******************************************************************
 * Lab8.c
 * Instructor: ***fill this in***
 * Runs on TM4C123
 * Use SysTick interrupts to implement a 4-key digital piano
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: ***fill this in***
 * Section: ***fill this in***
 * Date:    ***fill this in***
 *
 * Port B bits 3-0 have the 4-bit DAC
 * Port E bits 3-0 have 4 piano keys
 *******************************************************************/

#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "Piano.h"
#include "TExaS.h"

// basic functions defined at end of startup.s
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delay(unsigned long msec);


int main(void){ // Real Lab13 
	// for the real board grader to work 
	// you must connect PD3 to your DAC output
	// activate grader and set system clock to 80 MHz
	TExaS_Init(SW_PIN_PE3210, DAC_PIN_PB3210,ScopeOn);

	// PortE used for piano keys, PortB used for DAC        
	Sound_Init(); // initialize SysTick timer and DAC
	Piano_Init();
	EnableInterrupts();  // enable after all initialization are done

	while(1){                
		// input from keys to select tone

	}
            
}

void delay(unsigned long msec){ 
	unsigned long count;
	while(msec > 0 ) {  // repeat while there are still delay
		count = 16000;    // about 1ms
		while (count > 0) { 
			count--;
		} // This while loop takes approximately 3 cycles
		msec--;
	}
}
