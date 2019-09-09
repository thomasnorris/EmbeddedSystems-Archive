/*******************************************************************
 * TableTrafficLight.c
 * Instructor: ***fill this in***
 * Runs on LM4F120/TM4C123
 * Index implementation of a Moore finite state machine to operate a traffic light.  
 * Authors: Daniel Valvano,
 *					Jonathan Valvano,
 * 					Thomas Royko
 * Student: ***fill this in***
 * Section: ***fill this in***
 * Date:    ***fill this in***
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
#include "inc\tm4c123gh6pm.h"

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

int main(void){
	// activate grader and set system clock to 80 MHz
  TExaS_Init(SW_PIN_PE210, LED_PIN_PB543210,ScopeOff);
 
  
  EnableInterrupts();
  while(1){
     
  }
}

