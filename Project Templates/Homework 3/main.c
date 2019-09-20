// Program written by: Thomas Norris
// Date Created: 9/15/19
// Last Modified: 9/17/19
// Lab Section: 003
// Lab Instructor: Gursel Serpen
// Lab Project Number: 3
// Brief description of the program
// Hardware connections
//  PE3 is switch input  (1 means switch is not pressed, 0 means switch is pressed)
//  PE4 is switch input  (1 means switch is not pressed, 0 means switch is pressed)
//  PE5 is switch input  (1 means switch is not pressed, 0 means switch is pressed)
//  PE2 is LED output (0 means door is locked, 1 means door is unlocked) 
// The specific operation of this system is to 
//   unlock if all three switches are pressed

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

void PortE_Init(void);

int main(void){ 
	// inputs
	unsigned long PE3 = 0x08;            // 2_00001000
	unsigned long PE4 = 0x10;            // 2_00010000
	unsigned long PE5 = 0x20;            // 2_00100000
	
	// output
	unsigned long PE2 = 0x04;            // 2_00000100
	
	// init port E
	PortE_Init();
	
	// forever loop
	while(1) {
		// check input switches to set the output LED
		unsigned long SW1 = GPIO_PORTE_DATA_R & PE3; 
		unsigned long SW2 = GPIO_PORTE_DATA_R & PE4;
		unsigned long SW3 = GPIO_PORTE_DATA_R & PE5;
		
		if (!SW1 && !SW2 && !SW3)        // pull-up resistors used, negative logic
			GPIO_PORTE_DATA_R |= PE2;    // turn only pin 2 on by bitwise or with 2_00000100
		else
			GPIO_PORTE_DATA_R &= ~PE2;   // turn only pin 2 off by bitwise and with 2_11111011
	}
}

void PortE_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x10;
	while (!(SYSCTL_PRGPIO_R & 0x10)) {
		// wait for the clock to be active, do nothing in the mean time
	}
	
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTE_PCTL_R = 0x00;
	GPIO_PORTE_DIR_R = 0x04;
	GPIO_PORTE_PUR_R = 0x38;
	GPIO_PORTE_DEN_R = 0x3C;
}
