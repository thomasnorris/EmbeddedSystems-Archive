// Program written by: Thomas Norris
// Date Created: 10/27/19
// Last Modified: 10/27/19
// Lab Section: 003
// Lab Instructor: Gursel Serpen
// Homework Number: 7 - Question 1a

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

// include SysTick functions from SysTick.s
extern void SysTick_Init(void);
extern void SysTick_Wait(void);

void waitForMs(uint32_t);
void sysTickInit(void);

int main() {
	uint32_t delayInMs = 1;
	
	// initialize SysTick
	sysTickInit();
	
	while (1) {
		// wait a desired time in ms
		waitForMs(delayInMs);
		// do something after the wait
	}
}


void waitForMs(uint32_t delayInMs) {
	uint32_t oneMs = 50000;                     // 1 ms / 20 ns = 50000 counts
	delayInMs *= oneMs;                         // total delay
	NVIC_ST_RELOAD_R = delayInMs - 1;           // set the reload register
	NVIC_ST_CURRENT_R = 0;                      // clear the current value
	
	SysTick_Wait();                             // wait delayInMs
}

void sysTickInit(void) {
	// setting values stated in the question
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x05;
	
	SysTick_Init();
}
