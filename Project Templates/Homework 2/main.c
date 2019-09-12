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
#define N 25 // array size

unsigned long sum(unsigned long n) {
	unsigned long partial = 0;
	
	int i;
	for (i = 0; i <= n; ++i)
		partial += i;
	
	return partial;
}
unsigned long fun(unsigned long n) {
	return (n * (n + 1)) / 2;
}

int main(void) {
	unsigned long sumBuf[N], funBuf[N]; // arrays to store computed values
	int correctFlag;
	
	int i;
	for (i = 0; i < N; ++i) {
		sumBuf[i] = sum(i);
		funBuf[i] = fun(i);
		
		if (funBuf[i] != sumBuf[i]) {
			correctFlag = FALSE;        // instead of looping through the arrays a second time, make the comparison now
			return correctFlag;         // could also just return FALSE instead of setting the flag first
		}
	}
	
	correctFlag = TRUE;                 // all array values are equivalents
	return correctFlag;                 // again, could also just return TRUE instead of setting the flag first
}
