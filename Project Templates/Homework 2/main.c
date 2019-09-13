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

#define TRUE 1
#define FALSE 0
#define N 25                            // array size

unsigned long sum(unsigned long n) {
	unsigned long partial = 0;
	
	int i;
	for (i = 0; i <= n; ++i)            // sum the numbers from 0 up to n (inclusive)
		partial += i;
	
	return partial;
}
unsigned long fun(unsigned long n) {
	return (n * (n + 1)) / 2;           // use the formula to find the sum of numbers from 0 to n (inclusive)
}

int main(void) {
	unsigned long sumBuf[N], funBuf[N]; // arrays to store computed values
	int correctFlag;
	
	int i;
	for (i = 0; i < N; ++i) {           // for every number from 0 to N
		sumBuf[i] = sum(i);             // calculate sum(i) and store the value in sumBuf[i]
		funBuf[i] = fun(i);             // calculate fun(i) and store the value in funBuf[i]
		
		if (funBuf[i] != sumBuf[i]) {   // if the values stored in each array are not the same (the calculations were not the same)
			correctFlag = FALSE;        // the values are not correct, set the flag to FALSE
			return correctFlag;         // return the flag now instead of making any more comparisons since future comparisons are not necessary
		}
	}
	
	correctFlag = TRUE;                 // all array values are equal, set the flag to TRUE
	return correctFlag;                 // return the flag value
}
