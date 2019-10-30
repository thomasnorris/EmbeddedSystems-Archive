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

// definitions in Definitions.c

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

// initialization
void init(void);
extern void SysTick_Init(void);
void enableClock(char port);
void initPortA(void);
void initPortE(void);
void initPortF(void);

bool inputPressed(int reg, char pin) {
	return reg & pin;
}

void setOutput(int reg, char pin) {
	GPIO_PORTF_DATA_R = pin;
}

void disableOutput(int reg, char pin) {
	reg &= pin;
}

int main(void){
	// init everything
	init();
	
	while(1){
		if (inputPressed(PA_IN_DATA_REG, PA4_WALK_IN))
			setOutput(PF_OUT_DATA_REG, PF3_WALK_GREEN);
			
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
}

void initPortA() {
	enableClock(PA);
	
	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTA_PCTL_R = ZERO;
	GPIO_PORTA_PUR_R = PAX_PDR;
	GPIO_PORTA_DIR_R = PAX_DIR;
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
	// todo: changes here for led out
	GPIO_PORTF_DIR_R = PFX_DIR;
	GPIO_PORTF_DEN_R = PFX_DEN;
}

void enableClock(char port) {
	SYSCTL_RCGC2_R |= port;
	while (!(SYSCTL_RCGC2_R & port)) {
		// wait for clock to become active
	}
}
