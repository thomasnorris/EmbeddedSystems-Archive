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
void initPortA(void);
void initPortE(void);
void initPortF(void);
void enableClock(char port);

// I/O functions
char getNextInputIndex(void);
void setOutput(volatile uint32_t *reg, uint32_t data);

struct State {
	uint32_t Out;
	volatile uint32_t *Register;
	uint32_t Time; // 1 ms units
	uint32_t Next[8];
};

struct State FSM[22] = {
	{INIT_SW_OUT, PE_DATA, WAIT_MS, {initP, initP, initP, initP, initP, initP, initP, initP}},
	{INIT_P_OUT, PF_DATA, WAIT_MS, {goS, goS, goS, goS, goS, goS, goS, goS}},
	{GO_S_OUT, PE_DATA, GO_MS, {goS, waitS1, goS, waitS1, checkP1S, checkP1S, checkP1S, checkP1S}},
	{WAIT_SX_OUT, PE_DATA, WAIT_MS, {goW, goW, goW, goW, goW, goW, goW, goW}},
	{GO_W_OUT, PE_DATA, GO_MS, {goW, goW, waitW1, waitW1, checkP1W, checkP1W, checkP1W, checkP1W}},
	{WAIT_WX_OUT, PE_DATA, WAIT_MS, {goS, goS, goS, goS, goS, goS, goS, goS}},
	{CHECK_PXS_OUT, PE_DATA, CHECK_MS, {goS, goS, goS, goS, checkP2S, checkP2S, checkP2S, checkP2S}},
	{CHECK_PXS_OUT, PE_DATA, CHECK_MS, {goS, goS, goS, goS, waitS2, waitS2, waitS2, waitS2}},
	{WAIT_SX_OUT, PE_DATA, WAIT_MS, {haltSW, haltSW, haltSW, haltSW, haltSW, haltSW, haltSW, haltSW}},
	{HALT_SW_OUT, PE_DATA, WAIT_MS, {walkP, walkP, walkP, walkP, walkP, walkP, walkP, walkP}},
	{CHECK_PXW_OUT, PE_DATA, CHECK_MS, {goW, goW, goW, goW, checkP2W, checkP2W, checkP2W, checkP2W}},
	{CHECK_PXW_OUT, PE_DATA, CHECK_MS, {goW, goW, goW, goW, waitW2, waitW2, waitW2, waitW2}},
	{WAIT_WX_OUT, PE_DATA, WAIT_MS, {haltSW, haltSW, haltSW, haltSW, haltSW, haltSW, haltSW, haltSW}},
	{WALK_P_OUT, PF_DATA, WALK_MS, {warningP1Off, warningP1Off, warningP1Off, warningP1Off, warningP1Off, warningP1Off, warningP1Off, warningP1Off}},
	{WARNING_PX_OFF_OUT, PF_DATA, WARNING_MS, {warningP1On, warningP1On, warningP1On, warningP1On, warningP1On, warningP1On, warningP1On, warningP1On}},
	{WARNING_PX_ON_OUT, PF_DATA, WARNING_MS, {warningP2Off, warningP2Off, warningP2Off, warningP2Off, warningP2Off, warningP2Off, warningP2Off, warningP2Off}},
	{WARNING_PX_OFF_OUT, PF_DATA, WARNING_MS, {warningP2On, warningP2On, warningP2On, warningP2On, warningP2On, warningP2On, warningP2On, warningP2On}},
	{WARNING_PX_ON_OUT, PF_DATA, WARNING_MS, {warningP3Off, warningP3Off, warningP3Off, warningP3Off, warningP3Off, warningP3Off, warningP3Off, warningP3Off}},
	{WARNING_PX_OFF_OUT, PF_DATA, WARNING_MS, {warningP3On, warningP3On, warningP3On, warningP3On, warningP3On, warningP3On, warningP3On, warningP3On}},
	{WARNING_PX_ON_OUT, PF_DATA, WARNING_MS, {warningP4Off, warningP4Off, warningP4Off, warningP4Off, warningP4Off, warningP4Off, warningP4Off, warningP4Off}},
	{WARNING_PX_OFF_OUT, PF_DATA, WARNING_MS, {noWalkP, noWalkP, noWalkP, noWalkP, noWalkP, noWalkP, noWalkP, noWalkP}},
	{NO_WALK_P_OUT, PF_DATA, WAIT_MS, {goS, goW, goS, goS, goS, goW, goS, goS}}
};

int main(void){
	// get initial state
	struct State currentState = FSM[initSW];
	
	// activate grader and set system clock to 80 MHz
	TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210, ScopeOff);
	EnableInterrupts();

	// SysTick init
	SysTick_Init();

	// port init
	initPortA();
	initPortE();
	initPortF();
	
	// FSM
	while(1){
		// set the output to the corresponding register
		setOutput(currentState.Register, currentState.Out);
		
		// wait
		wait(currentState.Time);
		
		// get the next state and reassign based on the input
		currentState = FSM[currentState.Next[getNextInputIndex()]];
	}
}

void initPortA() {
	enableClock(PA);

	GPIO_PORTA_PDR_R = PAX_PDR;                  // enable PDRs
	GPIO_PORTA_DIR_R = ~PAX_DIR;                 // set input direction
	GPIO_PORTA_DEN_R = PAX_DEN;                  // digital enable
}

void initPortE() {
	enableClock(PE);

	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;           // unlock the port
	GPIO_PORTE_PCTL_R = ZERO;                    // clear PCTL
	GPIO_PORTE_DIR_R = PEX_DIR;                  // set output direction
	GPIO_PORTE_DEN_R = PEX_DEN;                  // digital enable
}

void initPortF() {
	enableClock(PF);

	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;           // unlock the port
	GPIO_PORTF_PCTL_R = ZERO;                    // clear PCTL
	GPIO_PORTF_DIR_R = PFX_DIR;                  // set output direction
	GPIO_PORTF_DEN_R = PFX_DEN;                  // digital enable
}

void enableClock(char port) {
	SYSCTL_RCGC2_R |= port;                      // enable the clock
	while (!(SYSCTL_RCGC2_R & port)) {
		// wait for clock to become active
	}
}

char getNextInputIndex() {
	char westIn = (*PA_DATA & WEST_IN) >> 2;    // shift from 0x04 to 0x01
	char southIn = (*PA_DATA & SOUTH_IN) >> 2;  // shift from 0x08 to 0x02
	char walkIn = (*PA_DATA & WALK_IN) >> 2;    // shift from 0x10 to 0x04
	
	return westIn | southIn | walkIn;           // bitwise OR to get a value between 0 and 7
}

void setOutput(volatile uint32_t *reg, uint32_t data) {
	*reg = data;
}

void wait(int ms) {
	int cyclesPerMs = 80000;                    // assuming 80MHz clock, 12.5 ns
	int i;
	for (i = 0; i < ms; ++i){
		SysTick_Wait(cyclesPerMs);              // wait 1 ms per loop
	}
}
