// Program written by: Thomas Norris
// Date Created: 10/27/19
// Last Modified: 10/27/19
// Lab Section: 003
// Lab Instructor: Gursel Serpen
// Homework Number: 7


#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

extern void removeAllChar(char str[], char toRemove);

// note: str[] is null-terminated by default
char str[] = "The Quick Brown Fox Jumps Over a Lazy Dog";
char toRemove = 'o';

int main() {
	removeAllChar(str, toRemove);
	
	// str should now be less the character toRemove
	
	while(1) {
		// forever
	}
}
