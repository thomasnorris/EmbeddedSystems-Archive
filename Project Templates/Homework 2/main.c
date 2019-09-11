/*******************************************************************
 *  main.c
 *  This is an embedded program template.
 *  
 *  Author: Thomas Norris
 *  Date: Date: 09/10/19
 *
 *  
 *******************************************************************/

// Called by startup assembly code, start of C code

int main(void) {
	int startVal = 5;
	int factorial = 1;
	
	for (startVal = startVal; startVal > 0; --startVal)
		factorial *= startVal;
	
	// do somthing with factorial
	
	while(1) {
		// do nothing
	}
}
