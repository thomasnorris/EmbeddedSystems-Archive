// Program written by: Thomas Norris
// Date Created: 10/27/19
// Last Modified: 10/27/19
// Lab Section: 003
// Lab Instructor: Gursel Serpen
// Homework Number: 7 - Question 7


#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

char str1[] = "str1";
char str2[] = "str2";

extern void Swap(char *str1, char *str2);

int main() {

	Swap(str1, str2);
	
	// str1 now equals str2 and str2 now equals str1
	
	while(1) {
		// forever
	}
}
