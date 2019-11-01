/*******************************************************************
 * TableTrafficLight.c
 * Instructor: Gursel Serpen
 * Runs on LM4F120/TM4C123
 * Index implementation of a Moore finite state machine to operate a traffic light.
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: Thomas Norris, Juliette Ulman
 * Section: 003
 * Date:    10/26/19
 *
 * see Definitions.c for pin connections
 *******************************************************************/

#include "TExaS.h"
#include <stdbool.h>
#include "inc\tm4c123gh6pm.h"
#include "Definitions.c"

// interrupt control
void DisableInterrupts(void);
void EnableInterrupts(void);

// SysTick
extern void SysTick_Init(void);
extern void SysTick_Wait(uint32_t cycles);
void wait(int ms);

// initialization
void init(void);
void initPortA(void);
void initPortE(void);
void initPortF(void);
void enableClock(char port);

// pin functions
bool isInput(char pin);
void setOutput(volatile uint32_t *reg, int pin, int pinToClear);

struct State {
	uint32_t Out;
	uint32_t Time; // 1 ms units
	uint32_t Next[8];
};

/*
struct State FSM[10] = {
	{}
};
*/

int main(void){
	// init everything, set default LED colors
	init();

	while(1){
		wait(1000);
		// test
		if (isInput(WALK_IN))
			setOutput(&PE_DATA, GREEN_SOUTH, RED_SOUTH);
		else
			setOutput(&PE_DATA, RED_SOUTH, GREEN_SOUTH);
	}
}

void init() {
	// activate grader and set system clock to 80 MHz
	TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210, ScopeOff);
	EnableInterrupts();

	// SysTick init
	SysTick_Init();

	// port init
	initPortA();
	initPortE();
	initPortF();

	// default sets all red LEDs
	setOutput(&PF_DATA, RED_WALK, ZERO);
	setOutput(&PE_DATA, RED_SOUTH, ZERO);
	setOutput(&PE_DATA, RED_WEST, ZERO);
}

void initPortA() {
	enableClock(PA);

	GPIO_PORTA_PDR_R = PAX_PDR;
	GPIO_PORTA_DIR_R = ~PAX_DIR;
	GPIO_PORTA_DEN_R = PAX_DEN;
}

void initPortE() {
	enableClock(PE);

	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTE_PCTL_R = ZERO;
	GPIO_PORTE_DIR_R = PEX_DIR;
	GPIO_PORTE_DEN_R = PEX_DEN;
}

void initPortF() {
	enableClock(PF);

	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTF_PCTL_R = ZERO;
	GPIO_PORTF_DIR_R = PFX_DIR;
	GPIO_PORTF_DEN_R = PFX_DEN;
}

void enableClock(char port) {
	SYSCTL_RCGC2_R |= port;
	while (!(SYSCTL_RCGC2_R & port)) {
		// wait for clock to become active
	}
}

bool isInput(char pin) {
	return PA_DATA & pin;
}

void setOutput(volatile uint32_t *reg, int pinToSet, int pinToClear) {
	*reg &= ~pinToClear;
	*reg |= pinToSet;
}

void wait(int ms) {
	int cyclesPerMs = 80000;   // assuming 80MHz clock, 12.5 ns
	int totalCycles = ms * cyclesPerMs;
	SysTick_Wait(totalCycles);
}
