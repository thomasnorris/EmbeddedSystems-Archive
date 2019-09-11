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

int maxValueArray[10] = {-1, 5, 3, 8, -10, 23, 6, 5, 2, 10};
int arraySize = 10;

int main(void) {
	int maxValue = 0;
	int i;
	
	for (i = 0; i < arraySize; ++i) {
		int currentValue = maxValueArray[i];
		if (currentValue >= maxValue)
			maxValue = currentValue;
	}
	
	// do something with maxValue
	
	while(1) {
		// do nothing
	}
}
