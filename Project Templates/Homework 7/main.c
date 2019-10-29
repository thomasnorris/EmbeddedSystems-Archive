// Program written by: Thomas Norris
// Date Created: 10/27/19
// Last Modified: 10/27/19
// Lab Section: 003
// Lab Instructor: Gursel Serpen
// Homework Number: 7


#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

extern void max4(int32_t int1, int32_t int2, int32_t int3, int32_t int4);

int main() {
	int32_t int1 = 8;
	int32_t int2 = 2;
	int32_t int3 = 4;
	int32_t int4 = 3;
	
	max4(int1, int2, int3, int4);
	
	// int1 is now the max
	
	while(1) {
		// forever
	}
}
