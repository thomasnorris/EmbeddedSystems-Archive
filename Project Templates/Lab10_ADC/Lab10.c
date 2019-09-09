/*******************************************************************
 * Lab10.c
 * Copyright 2014 by Jonathan W. Valvano, valvano@mail.utexas.edu
 * Adapted by Thomas Royko, Gursel Serpen
 * Runs on TM4C123
 * 
 * Instructor: ***fill this in***
 * Student: ***fill this in***
 * Section: ***fill this in***
 * Date:    ***fill this in***
 *
 * Analog Input connected to PE2=ADC1
 * displays on Sitronox ST7735
 * PF3, PF2, PF1 are heartbeats
 *******************************************************************/

#include <stdint.h>
#include <stdio.h>

#include "ST7735.h"
#include "TExaS.h"
#include "ADC.h"
#include "print.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"

//*****the first three main programs are for debugging *****
// main1 tests just the ADC and slide pot, use debugger to see data
// main2 adds the LCD to the ADC and slide pot, ADC data is on ST7735
// main3 adds your convert function, position data is no ST7735

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void TExaS_Stop(void);	

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
	
// Initialize Port F so PF1, PF2 and PF3 are heartbeats
// Please use the SYSCTL_RCGCGPIO_R instead of SYSCTL_RCGC2_R 
void PortF_Init(void){

}

unsigned long Flag;   // 1 means valid Distance, 0 means Distance is empty
uint32_t Data;        // 12-bit ADC
double Position;    // 32-bit fixed-point 0.001 cm

int PartC(void){      // single step this program and look at Data
  ADC_Init();         // turn on ADC, set channel to 1
  while(1){                
    Data = ADC_In();  // sample 12-bit channel 1
  }
}

int PartD(void){
	PortF_Init();
  ST7735_InitR(INITR_REDTAB);
	ADC_Init();         // turn on ADC, set channel to 1
	
  while(1){           // use scope to measure execution time for ADC_In and LCD_OutDec           
    PF2 = 0x04;       // Profile ADC
    Data = ADC_In();  // sample 12-bit channel 1
    PF2 = 0x00;       // end of ADC Profile
    ST7735_SetCursor(0,0);
    PF1 = 0x02;       // Profile LCD
    ST7735_OutUDec(Data);
    ST7735_OutString("    ");  // these spaces are used to coverup characters from last output
    PF1 = 0;          // end of LCD Profile */
  }
}

double Convert(uint32_t input){
  return 0;
}

int PartE(void){
	PortF_Init();
	ST7735_InitR(INITR_REDTAB); 
  ADC_Init();         // turn on ADC, set channel to 1
	
  while(1){  
    PF2 ^= 0x04;      // Heartbeat
    Data = ADC_In();  // sample 12-bit channel 1
    PF3 = 0x08;       // Profile Convert
    Position = Convert(Data); 
    PF3 = 0;          // end of Convert Profile
    PF1 = 0x02;       // Profile LCD
    ST7735_SetCursor(0,0);
    ST7735_OutUDec(Data);
    ST7735_SetCursor(0,3);
		char buf [10];
		sprintf (buf, "%.2f mm", Position);
		ST7735_OutString(buf);
    PF1 = 0;          // end of LCD Profile
  }
}

int main(void){
  TExaS_Init();
	PLL_Project10();
	//Only call one function at a time
	//Uncomment to enable code for each project section
  //PartC();
	//PartD();
	//PartE();
}

