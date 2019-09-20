// Program written by: Thomas Norris
// Date Created: 9/20/19
// Last Modified: 9/20/19
// Lab Instructor: Gursel Serpen
// Homework Number: 3

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

void PortE_Init(void);

int main(void){
	
	// init port E
	PortE_Init();
	
	// forever loop
	while(1) {
		
	}
}

void PortE_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x10;
	while (!(SYSCTL_PRGPIO_R & 0x10)) {
		// wait for the clock to be active, do nothing in the mean time
	}
	
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTE_PCTL_R = 0x00;
	
	// settings from lab 3
	GPIO_PORTE_DIR_R = 0x04;
	GPIO_PORTE_PUR_R = 0x38;
	GPIO_PORTE_DEN_R = 0x3C;
}
