// Program written by:
// Date Created:
// Last Modified: 
// Lab Section:
// Lab Instructor: 
// Lab Project Number:
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

int main(void){ 
  
	volatile unsigned long delay;
	// Init Port E
	
	while(1){
			// check input switches to set the output LED

  }
}

