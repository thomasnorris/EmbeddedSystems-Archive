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
	int start_val = 5;
	int factorial = 1;
	
	while (start_val) {
		factorial *= start_val;
		--start_val;
	}
	
	// do somthing with factorial
	
	while(1) {
		// do nothing
	}
}
