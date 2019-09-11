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

void checkBitValue(void);
void setBitValue(void);
void clearBitValue(void);
void toggleBitValue(void);

int main(void) {

	while(1) {
		checkBitValue();
		setBitValue();
		clearBitValue();
		toggleBitValue();
	}
}

void checkBitValue(void) {
	char ch1 = 0x34;      // 0x34 = 2_00110100
	char mask = 0x20;     // 0x20 = 2_00100000
	char ch2;
	
	if (ch1 & mask)       // yeilds 2_00100000
		ch2 = 1;
	else
		ch2 = 0;
}

void setBitValue(void) {
	char ch1 = 0x34;      // 0x34 = 2_00110100
	char mask = 0x80;     // 0x80 = 2_10000000
	
	ch1 |= mask;          // sets ch1 to 2_10110100
}

void clearBitValue(void) {
	char ch1 = 0x34;      // 0x34 = 2_00110100
	char mask = 0x34;     // 0x34 = 2_00110100
	
	ch1 &= mask;          // sets ch1 to 2_00110100
}

void toggleBitValue(void) {

}
