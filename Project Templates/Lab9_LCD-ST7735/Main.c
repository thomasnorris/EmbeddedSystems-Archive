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

void Delay1ms(uint32_t n);
extern void IO_Init(void);
extern void IO_HeartBeat(void);
extern void IO_Touch(void);

void delay2S(void);
void clearScreen(void);
void drawNames(void);
void drawPicture(void);
void drawCatchPhrases(void);
void breakPointMode(void);

int main(void){
	PLL_Init(); // set system clock to 80 MHz
	IO_Init();
  
	// test DrawChar() and DrawCharS()
	ST7735_InitR(INITR_REDTAB);
	
	unsigned long in = 0x00000000;
	bool breakEnabled;
	
	while(1) {
		breakEnabled = false;
		clearScreen();
		
		// read inputs
		in = GPIO_PORTE_DATA_R & 0x07;
		if (in & 0x01)
			breakEnabled = true;
		
		switch(in) {
			case 0x02:
			case 0x03:
				if (breakEnabled)
					IO_Touch();
				drawNames();
				if (breakEnabled)
					IO_Touch();
				drawCatchPhrases();
				break;
			case 0x04:
			case 0x05:
				if (breakEnabled)
					IO_Touch();
				drawPicture();
				break;
			case 0x06:
			case 0x07:
				if (breakEnabled)
					IO_Touch();
				drawNames();
				if (breakEnabled)
					IO_Touch();
				drawCatchPhrases();
				if (breakEnabled)
					IO_Touch();
				drawPicture();
				break;
		}
		
		// delay 2 seconds
		delay2S();
		IO_HeartBeat();
	}
}

void delay2S() {
	for (int i = 0; i < 2000; ++i) {
		Delay1ms(5);
	}
}

void clearScreen() {
	ST7735_FillScreen(0x0000);
}

void drawNames() {
	ST7735_DrawString(0, 0, "Thomas Norris", 0xF800);
	ST7735_DrawString(0, 1, "Juliette Ulman", 0xF81F);
}

void drawPicture() {
	ST7735_DrawBitmap(30, 110, UT, 64, 64);
}

void drawCatchPhrases() {
	ST7735_DrawString(0, 14, "I like trains", 0xF800);
	ST7735_DrawString(0, 15, "I love UT", 0xF81F);
}
