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
 * east/west red light connected to PB5
 * east/west yellow light connected to PB4
 * east/west green light connected to PB3
 * north/south facing red light connected to PB2
 * north/south facing yellow light connected to PB1
 * north/south facing green light connected to PB0
 * pedestrian detector connected to PE2 (1=pedestrian present)
 * north/south car detector connected to PE1 (1=car present)
 * east/west car detector connected to PE0 (1=car present)
 * "walk" light connected to PF3 (built-in green LED)
 * "don't walk" light connected to PF1 (built-in red LED)
 *******************************************************************/

#include "TExaS.h"
#include <stdbool.h>
#include "inc\tm4c123gh6pm.h"
#include "Definitions.c"

// definitions in Definitions.c for more intuitive naming

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// initialization
void init(void);
extern void SysTick_Init(void);
void enableClock(char port);
void initPortA(void);
void initPortE(void);
void initPortF(void);

// pin functions
bool isInput(char pin);
void setOutput(volatile uint32_t *reg, int pin, int pinToClear);

int main(void){
	// init everything, set default LED colors
	init();
	
	while(1){
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
