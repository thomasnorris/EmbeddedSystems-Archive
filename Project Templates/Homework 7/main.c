// Program written by: Thomas Norris
// Date Created: 10/27/19
// Last Modified: 10/27/19
// Lab Section: 003
// Lab Instructor: Gursel Serpen
// Homework Number: 7 - Question 1b


#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

extern void SysTick_Init(void);
extern void SysTick_Wait(void);

void interruptAfterUs(uint32_t);
void sysTickInit(void);

int main() {
	uint32_t delayInUs = 100;
	
	// initialize SysTick
	sysTickInit();
	
	while(1) {
		// wait a desired time in us
		interruptAfterUs(delayInUs);
		// do something after the wait
	}
}

void interruptAfterUs(uint32_t delayInUs) {
	uint32_t oneUs = 80;                        // 1 us / 12.5 ns = 80 counts
	delayInUs *= oneUs;                         // total delay
	NVIC_ST_RELOAD_R = delayInUs - 1;           // set the reload register
	NVIC_ST_CURRENT_R = 0;                      // clear the current value
	
	SysTick_Wait();                             // wait delayInUs and interrupt
}

void sysTickInit(void) {
	// setting values stated in the question
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x07;     // 0x07 = 0111b which sets CLK_SRC = 1, INTEN = 1, and ENABLE = 1
	
	SysTick_Init();
}
