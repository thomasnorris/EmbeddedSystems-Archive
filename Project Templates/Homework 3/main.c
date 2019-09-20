// Program written by: Thomas Norris
// Date Created: 9/20/19
// Last Modified: 9/20/19
// Lab Instructor: Gursel Serpen
// Homework Number: 3

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

//void PortE_Init(void);
void initPortA(void);
void initPortB(void);
void initPortC(void);
void initPortD(void);

int main(void){
	
	// init port E
	// PortE_Init();
	
	initPortA();
	initPortB();
	initPortC();
	initPortD();
	
	// forever loop
	while(1) {
		
	}
}

void initPortA(void) {
	unsigned long portHex = 0x00;
	
	SYSCTL_RCGCGPIO_R |= portHex;
	while (!(SYSCTL_PRGPIO_R & portHex)) {
	}
	
	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTA_PCTL_R = 0x00;
}

void initPortB(void) {
	unsigned long portHex = 0x00;
	
	SYSCTL_RCGCGPIO_R |= portHex;
	while (!(SYSCTL_PRGPIO_R & portHex)) {
	}
	
	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTB_PCTL_R = 0x00;
}

void initPortC(void) {
	unsigned long portHex = 0x00;
	
	SYSCTL_RCGCGPIO_R |= portHex;
	while (!(SYSCTL_PRGPIO_R & portHex)) {
	}
	
	GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTC_PCTL_R = 0x00;
}

void initPortD(void) {
	unsigned long portHex = 0x00;
	
	SYSCTL_RCGCGPIO_R |= portHex;
	while (!(SYSCTL_PRGPIO_R & portHex)) {
	}
	
	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTD_PCTL_R = 0x00;
}

void PortE_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x10;
	while (!(SYSCTL_PRGPIO_R & 0x10)) {
	}
	
	GPIO_PORTE_LOCK_R = GPIO_LOCK_KEY;
	GPIO_PORTE_PCTL_R = 0x00;
	
	// settings from lab 3
	GPIO_PORTE_DIR_R = 0x04;
	GPIO_PORTE_PUR_R = 0x38;
	GPIO_PORTE_DEN_R = 0x3C;
}
