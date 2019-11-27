/*******************************************************************
 * Main.c
 * Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
 * Adapted by Thomas Royko, Gursel Serpen
 * Runs on TM4C123
 * 
 * Instructor: Gursel Serpen
 * Student: Thomas Norris, Juliette Ulman
 * Section: 003
 * Date: 11/27/19
 *
 * 16-bit color, 128 wide by 160 high LCD
 *   Backlight (pin 10) connected to +3.3 V
 *   MISO (pin 9) unconnected 
 *   SCK (pin 8) connected to PA2 (SSI0Clk)
 *   MOSI (pin 7) connected to PA5 (SSI0Tx)
 *   TFT_CS (pin 6) connected to PA3 (SSI0Fss)
 *   CARD_CS (pin 5) unconnected
 *   Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
 *   RESET (pin 3) connected to PA7 (GPIO)
 *   VCC (pin 2) connected to +3.3 V
 *   Gnd (pin 1) connected to ground
 *******************************************************************/

#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "Images.h"
#include "../inc/tm4c123gh6pm.h"

typedef enum { false, true } bool;

void Delay1ms(void);
extern void IO_Init(void);
extern void IO_HeartBeat(void);
extern void IO_Touch(void);

int main(void){
	PLL_Init(); // set system clock to 80 MHz
	IO_Init();
  
	// test DrawChar() and DrawCharS()
	ST7735_InitR(INITR_REDTAB);
	
	unsigned long in = 0x00000000;
	bool breakEnabled = false;
	
	while(1) {
		//Input and display code goes here
		//See assignment for psuedo code
		
		// delay 2 seconds
		for (int i = 0; i < 2000; ++i) {
			Delay1ms();
		}
		IO_HeartBeat();
	}
}

void Delay1ms(void) {
	unsigned long count = 16000;
	while (count > 0) {
		count--;
	}
}
