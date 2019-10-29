// Program written by: Thomas Norris
// Date Created: 10/27/19
// Last Modified: 10/27/19
// Lab Section: 003
// Lab Instructor: Gursel Serpen
// Homework Number: 7


#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

char src[25] = "Hello!";
char dst[25];

extern void strcpy(char dst[25], char src[25]);

int main() {
	
	strcpy(dst, src);
	
	while(1) {
		// forever
	}
}
