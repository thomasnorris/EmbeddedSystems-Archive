// Program written by: Thomas Norris
// Date Created: 9/20/19
// Last Modified: 9/20/19
// Lab Instructor: Gursel Serpen
// Homework Number: 3

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

unsigned long initPortA(void);
unsigned long initPortB(void);
void initPortC(void);
void initPortD(void);
void question5(unsigned long);

int main(void){
	
	// init functions
	initPortA();                            // do not use the return value
	initPortB();                            // do not use the return value
	initPortC();
	initPortD();
	
	unsigned long threeBitValue = 0x02;     // can be any value from 0 to 0x07 (three bits)
	if (threeBitValue <= 0x07)              // check to make sure it is valid
		question5(threeBitValue);           // call the function with the supplied value
	
	// forever loop
	while(1) {

	}
}

// port A pin 7 INPUT
unsigned long initPortA(void) {
	unsigned long portHex = 0x01;            // hex value for port A
	unsigned long pinHex = 0x80;             // hex value for pin 7

	SYSCTL_RCGCGPIO_R |= portHex;            // enable the clock for pin 7
	while (!(SYSCTL_PRGPIO_R & portHex)) {   // wait for the clock to be active
	}

	GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;       // unlock port A
	GPIO_PORTA_PCTL_R = 0x00;                // clear the PCTL register
	GPIO_PORTA_DIR_R = 0x00;                 // set pin 7 as input
	GPIO_PORTA_PDR_R = pinHex;               // enable pull-down reisistor on pin 7 (positive logic)
	GPIO_PORTA_DEN_R = pinHex;               // enable pin 7
	
	return GPIO_PORTA_DATA_R & pinHex;       // read pin 7 and return the value
}

// port B pin 0 INPUT
unsigned long initPortB(void) {
	unsigned long portHex = 0x02;            // hex value for port B
	unsigned long pinHex = 0x01;             // hex value for pin 0

	SYSCTL_RCGCGPIO_R |= portHex;            // enable the clock for pin 0
	while (!(SYSCTL_PRGPIO_R & portHex)) {   // wait for the clock to be active
	}

	GPIO_PORTB_LOCK_R = GPIO_LOCK_KEY;       // unlock port B
	GPIO_PORTB_PCTL_R = 0x00;                // clear the PCTL register
	GPIO_PORTB_DIR_R = 0x00;                 // set pin 0 as input
	GPIO_PORTB_PUR_R = pinHex;               // enable pull-up reisistor on pin 0 (negative logic)
	GPIO_PORTB_DEN_R = pinHex;               // enable pin 0
	
	return GPIO_PORTB_DATA_R & portHex;      // read pin 0 and return the value
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
	GPIO_PORTC_DIR_R = pinHex;               // set pin 6 as output
	GPIO_PORTC_DEN_R = pinHex;               // enable pin 6
	
	GPIO_PORTC_DATA_R |= pinHex;             // write a 1 to pin 6
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
	GPIO_PORTD_DIR_R = pinHex;               // set pin 4 as output
	GPIO_PORTD_DEN_R = pinHex;               // enable pin 4
	
	GPIO_PORTD_DATA_R |= pinHex;             // write a 1 to pin 4
}

// port A pins 3, 4, 5 OUTPUT
void question5(unsigned long threeBitValue) {
	unsigned long pin345Hex = 0x38;          // 2_00111000
	
	if (!(SYSCTL_PRGPIO_R & 0x01))           // port A should be initialized, but if there is no clock that is not the case, so initPortA()
		initPortA();
	
	threeBitValue <<= 3;                     // bit shift to the left by 3 to represent pins 3, 4, 5 instead of 0, 1, 2
	
	GPIO_PORTA_DIR_R |= pin345Hex;           // set ONLY pins 3, 4, 5 to output (pin 7 and all others are still input from initPortA())
	GPIO_PORTA_DEN_R |= pin345Hex;           // enable ONLY pins 3, 4, 5 (pin 7 is enabled from initPortA())
	GPIO_PORTA_DATA_R |= threeBitValue;      // set ONLY pins 3, 4, 5 to threeBitValue
}
