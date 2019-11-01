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
 * see Definitions.c for definitions
 *******************************************************************/

#include "TExaS.h"
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
void initAll(void);
void initPortA(void);
void initPortE(void);
void initPortF(void);
void enableClock(char port);

// pin functions
uint32_t getNextInputIndex(void);
void setOutput(volatile uint32_t *reg, uint32_t data);

struct State {
	uint32_t Out;
	volatile uint32_t *Register;
	uint32_t Time; // 1 ms units
	uint32_t Next[8];
};


struct State FSM[15] = {
	{GO_S_OUT, &PE_DATA, GO_MS, {goS, waitS, goS, waitS, waitS, waitS, waitS, waitS}},
	{WAIT_S_OUT, &PE_DATA, WAIT_MS, {goW, goW, goW, goW, checkP1, checkP1, checkP1, checkP1}},
	{GO_W_OUT, &PE_DATA, GO_MS, {goW, goW, waitW, waitW, waitW, waitW, waitW, waitW}},
	{WAIT_W_OUT, &PE_DATA, WAIT_MS, {goS, goS, goS, goS, checkP1, checkP1, checkP1, checkP1}},
	{CHECK_PX_OUT, &PE_DATA, CHECK_MS, {goS, goS, goS, goS, checkP2, checkP2, checkP2, checkP2}},
	{CHECK_PX_OUT, &PE_DATA, CHECK_MS, {goS, goS, goS, goS, stopAll, stopAll, stopAll, stopAll}},
	{STOP_ALL_OUT, &PE_DATA, STOP_MS, {walkP, walkP, walkP, walkP, walkP, walkP, walkP, walkP}},
	{WALK_P_OUT, &PF_DATA, WAIT_MS, {warningP1Off, warningP1Off, warningP1Off, warningP1Off, warningP1Off, warningP1Off, warningP1Off, warningP1Off}},
	{WARNING_PX_OFF_OUT, &PF_DATA, WARNING_MS, {warningP1On, warningP1On, warningP1On, warningP1On, warningP1On, warningP1On, warningP1On, warningP1On}},
	{WARNING_PX_ON_OUT, &PF_DATA, WARNING_MS, {warningP2Off, warningP2Off, warningP2Off, warningP2Off, warningP2Off, warningP2Off, warningP2Off, warningP2Off}},
	{WARNING_PX_OFF_OUT, &PF_DATA, WARNING_MS, {warningP2On, warningP2On, warningP2On, warningP2On, warningP2On, warningP2On, warningP2On, warningP2On}},
	{WARNING_PX_ON_OUT, &PF_DATA, WARNING_MS, {warningP3Off, warningP3Off, warningP3Off, warningP3Off, warningP3Off, warningP3Off, warningP3Off, warningP3Off}},
	{WARNING_PX_OFF_OUT, &PF_DATA, WARNING_MS, {warningP3On, warningP3On, warningP3On, warningP3On, warningP3On, warningP3On, warningP3On, warningP3On}},
	{WARNING_PX_ON_OUT, &PF_DATA, WARNING_MS, {warningP4Off, warningP4Off, warningP4Off, warningP4Off, warningP4Off, warningP4Off, warningP4Off, warningP4Off}},
	{NO_WALK_P_OUT, &PF_DATA, WAIT_MS, {goS, goW, goS, goW, checkP1, goW, goS, goW}}
};



int main(void){
	struct State currentState = FSM[goS];
	
	// init everything
	initAll();
	
	while(1){
		setOutput(currentState.Register, currentState.Out);
		wait(currentState.Time);
		currentState = FSM[currentState.Next[getNextInputIndex()]];
	}
}

void initAll() {
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

uint32_t getNextInputIndex() {
	switch (PA_DATA & ALL_INPUTS) {
		case 0x04:
			return 1;
		case 0x08:
			return 2;
		case 0x0C:
			return 3;
		case 0x10:
			return 4;
		case 0x14:
			return 5;
		case 0x18:
			return 6;
		case 0x1C:
			return 7;
	}
	return 0;
}

void setOutput(volatile uint32_t *reg, uint32_t data) {
	*reg = data;
}

void wait(int ms) {
	int cyclesPerMs = 80000;   // assuming 80MHz clock, 12.5 ns
	int totalCycles = ms * cyclesPerMs;
	SysTick_Wait(totalCycles);
}
