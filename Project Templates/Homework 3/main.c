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

// DIR: 0 = INPUT
//      1 = OUTPUT

// port A pin 7 INPUT
void initPortA(void) {
	unsigned long portHex = 0x01;            // hex value for port A
	unsigned long pinHex = 0x80;             // hex value for pin 7

	SYSCTL_RCGCGPIO_R |= portHex;            // enable the clock for pin 7
	while (!(SYSCTL_PRGPIO_R & portHex)) {   // wait for the clock to be active
	}

	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;       // unlock port A
	GPIO_PORTA_PCTL_R = 0x00;                // clear the PCTL register
	GPIO_PORTA_DATA_R = 0x00;                // set pin 7 as input
	GPIO_PORTA_PDR_R = pinHex;               // enable pull-down reisistor on pin 7 (positive logic)
	GPIO_PORTA_DEN_R = pinHex;               // enable pin 7
}

// port B pin 0 INPUT
void initPortB(void) {
	unsigned long portHex = 0x02;            // hex value for port B
	unsigned long pinHex = 0x01;             // hex value for pin 0

	SYSCTL_RCGCGPIO_R |= portHex;            // enable the clock for pin 0
	while (!(SYSCTL_PRGPIO_R & portHex)) {   // wait for the clock to be active
	}

	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;       // unlock port B
	GPIO_PORTB_PCTL_R = 0x00;                // clear the PCTL register
	GPIO_PORTB_DATA_R = 0x00;                // set pin 0 as input
	GPIO_PORTB_PUR_R = pinHex;               // enable pull-up reisistor on pin 0 (negative logic)
	GPIO_PORTB_DEN_R = pinHex;               // enable pin 0
}

// port C pin 6 OUTPUT
void initPortC(void) {
	unsigned long portHex = 0x04;            // hex value for port C
	unsigned long pinHex = 0x40;             // hex value for pin 6

	SYSCTL_RCGCGPIO_R |= portHex;            // enable the clock for pin 6
	while (!(SYSCTL_PRGPIO_R & portHex)) {   // wait for the clock to be active
	}

	GPIO_PORTC_LOCK_R = GPIO_LOCK_KEY;       // unlock port C
	GPIO_PORTC_PCTL_R = 0x00;                // clear the PCTL register
	GPIO_PORTC_DATA_R = pinHex;              // set pin 6 as output
	// GPIO_PORTC_DEN_R = pinHex;            // do not enable pin 6 (yet)
}

// port D pin 4 OUTPUT
void initPortD(void) {
	unsigned long portHex = 0x08;            // hex value for port D
	unsigned long pinHex = 0x10;             // hex value for pin 4

	SYSCTL_RCGCGPIO_R |= portHex;            // enable the clock for pin 4
	while (!(SYSCTL_PRGPIO_R & portHex)) {   // wait for the clock to be active
	}

	GPIO_PORTD_LOCK_R = GPIO_LOCK_KEY;       // unlock port D
	GPIO_PORTD_PCTL_R = 0x00;                // clear the PCTL register
	GPIO_PORTD_DATA_R = pinHex;              // set pin 4 as output
	GPIO_PORTD_DEN_R = pinHex;               // enable pin 4
}
