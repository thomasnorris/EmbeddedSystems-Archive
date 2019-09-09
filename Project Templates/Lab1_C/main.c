/*******************************************************************
 *  main.c
 *  This is your first program to run on the LaunchPad
 *  Lab 1, Inputs from PF4,PF0, output to PF3,PF2,PF1 (LED)
 *  Authors: Daniel Valvano
 *           Jonathan Valvano
 *           Ramesh Yerraballi
 *           Thomas Royko
 *  Date: Date: November 17, 2016
 *
 *  LaunchPad built-in hardware
 *  SW1 left switch is negative logic PF4 on the Launchpad
 *  red LED connected to PF1 on the Launchpad
 *  blue LED connected to PF2 on the Launchpad
 *  green LED connected to PF3 on the Launchpad
 *
 *  When SW1 is pressed,     LED should flash BLUE and GREEN
 *  When SW1 is not pressed, LED should flash BLUE and RED
 *******************************************************************/

// TExaS.o is the object code for the real-board grader
#include "TExaS.h"

// Constant declarations to access port registers using 
// symbolic names instead of addresses
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))

// Color LED(s) PortF
#define LED_OFF                 0x00  // dark     ---    0
#define LED_RED                 0x02  // red      R--    0x02
#define LED_BLUE                0x04  // blue     --B    0x04
#define LED_GREEN               0x08  // green    -G-    0x08
#define LED_YELLOW              0x0A  // yellow   RG-    0x0A
#define LED_SKYBLUE             0x0C  // sky blue -GB    0x0C
#define LED_WHITE               0x0E  // white    RGB    0x0E
#define LED_PINK                0x06  // pink     R-B    0x06

void InitPortF(void);
void Delay(void);
void EnableInterrupts(void);

unsigned long SW1;  // input from PF4

// Called by startup assembly code, start of C code
int main(void){    
	
	// Initialize real board grader
  TExaS_Init(SW_PIN_PF40,LED_PIN_PF321);
	// Initialize port PF4, PF3, PF2, PF1, PF0
	InitPortF();
	// The grader uses interrupts
	EnableInterrupts();
	
  while(1){
		SW1 = GPIO_PORTF_DATA_R & 0x10; // read PF4 into In
    
		if(SW1 == 0x00){ // zero means SW1 is pressed
      GPIO_PORTF_DATA_R = LED_GREEN;
		}
		else{           // 0x10 means SW1 is not pressed
      GPIO_PORTF_DATA_R = LED_RED;
    }
		
    Delay();
    GPIO_PORTF_DATA_R = LED_BLUE;
    Delay();
  }
}

// Initializes port F pins for input and output
void InitPortF(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0        
}

// Waits for 0.1 sec
void Delay(void){
	unsigned long volatile time;
  time = 727240 * 200 / 91;  // 0.1sec
  while(time){
		time--;
  }
}
