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

const unsigned short UT[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xEF3C,
 0xFF5B, 0xFFBD, 0xFF7D, 0xFFFE, 0xFFFF, 0xFFFF, 0xCDD6, 0xEEFB, 0xFFFE, 0xFF9C, 0xFF9B, 0xFFFD, 0xF6FA, 0xFF5B, 0xEEFA, 0xFFFF,
 0xFF7B, 0xFF7B, 0xFF9C, 0xFF3A, 0xFF5B, 0xFFFE, 0xFF9C, 0xF6F9, 0xF71A, 0xFF9C, 0xFFFE, 0xFFFD, 0xFFDD, 0xFFFE, 0xFFFE, 0xDE98,
 0xDED9, 0xFFFE, 0xFFFF, 0xFFFF, 0xF7BE, 0xFFFF, 0xF7DF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xF77D, 0xDEBA,
 0x6268, 0x93CD, 0xF71B, 0xFFFF, 0xF73C, 0x9430, 0x940F, 0x942F, 0xACD1, 0xFFFD, 0xF6D9, 0x72C9, 0x7B2B, 0x9C4F, 0x732C, 0xD617,
 0x9C4F, 0x6AC9, 0x836B, 0x8BAC, 0xACB1, 0xE698, 0x838C, 0x6AC9, 0x8BED, 0xA490, 0xCDF5, 0xFFFE, 0xFFFE, 0xFFBC, 0x8BED, 0x940E,
 0x9490, 0x8C4F, 0xF79C, 0xFFFE, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xEF3C,
 0x8B8C, 0xBCF1, 0xFFFE, 0xFFFE, 0xA4D2, 0x730C, 0xFF3B, 0xFF7C, 0x836B, 0xE677, 0xFFFE, 0x8B6B, 0x9C2F, 0xF6FA, 0xCDD6, 0xDE59,
 0xEEB8, 0x6288, 0xE698, 0xFF7B, 0xACD1, 0xFF3A, 0xA4B0, 0x7B4B, 0xFFDD, 0xC594, 0x7B6B, 0xD616, 0xFFFD, 0xACD1, 0x732A, 0xFFBC,
 0xEEFA, 0x83CD, 0xD678, 0xFFFE, 0xFFFF, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF,
 0x7B0A, 0xCD94, 0xFFFE, 0xFFBD, 0x6ACA, 0xA4B2, 0xFFFF, 0xFFDE, 0xB4F1, 0x8BAC, 0xFFDC, 0xA42E, 0x9C2F, 0xFFFE, 0xFFFF, 0xE6DA,
 0xEEB8, 0x72C9, 0xFF7B, 0xFFFD, 0xF6F9, 0xFFFE, 0xA46F, 0x940E, 0xFFFE, 0xFFFE, 0xA490, 0x942E, 0xFFBC, 0x732A, 0xBD73, 0xFFFD,
 0xFFFE, 0x9C91, 0x83EE, 0xFF9D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBE, 0xFFDF, 0xFFFF, 0xFFDF,
 0x8B6A, 0xE615, 0xFFFD, 0xEE98, 0x49C6, 0xE699, 0xFFFE, 0xFFFE, 0xDE36, 0x7AE9, 0xFF9C, 0x9C2E, 0xA470, 0xFFDD, 0xFFFF, 0xFFFF,
 0xE677, 0x6AA8, 0xFF1A, 0xFF7B, 0xFFFE, 0xFFFE, 0xACD0, 0x940E, 0xFFDD, 0xFFFE, 0xC5B4, 0x6267, 0xD615, 0x5206, 0xEEF9, 0xFFDD,
 0xFFFE, 0xC595, 0x5A68, 0xFF9D, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFF9E,
 0x8329, 0xCD72, 0xFFFE, 0xDE36, 0x5A68, 0xF73B, 0xFFBD, 0xFFDD, 0xD5B4, 0x5A26, 0xFF3A, 0x9C2E, 0xACD1, 0xFFFE, 0xFFDF, 0xFFFF,
 0xFF1A, 0x5A06, 0xD5F5, 0xCDB4, 0xFF5B, 0xFF9C, 0xBD53, 0x93ED, 0xFFFD, 0xFFBC, 0xDE77, 0x72E9, 0xBD73, 0x5A47, 0xE697, 0xFFFE,
 0xFFFE, 0xEEB9, 0x5A68, 0xF71B, 0xFFFF, 0xFF9E, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF,
 0x93AB, 0xCD72, 0xFFFD, 0xDE15, 0x5A48, 0xF71B, 0xFFDE, 0xFFFE, 0xEE98, 0x6267, 0xFF3A, 0x940D, 0x9C50, 0xFFFE, 0xFFFF, 0xFFFF,
 0xEE98, 0x5A06, 0x9C2E, 0x834B, 0xFF7B, 0xFFFE, 0xA48F, 0x9C2E, 0xFFFE, 0xFFFE, 0xE6B8, 0x5206, 0x9C4F, 0x6AC9, 0xF71A, 0xFFFE,
 0xFFFE, 0xDE37, 0x51E7, 0xE679, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFDF,
 0x938A, 0xD592, 0xFFFD, 0xEE97, 0x5207, 0xFF7C, 0xFFFE, 0xFFDD, 0xCDB4, 0x6A88, 0xFF3A, 0x9C2E, 0xA4B1, 0xFFFE, 0xFFBE, 0xFFFF,
 0xF6D9, 0x6A88, 0xF6F9, 0xDE16, 0xFF1A, 0xFFFE, 0xACB0, 0x940E, 0xFFFE, 0xFFFE, 0xCDD5, 0x6AC9, 0xD616, 0x5A67, 0xF71A, 0xFFDD,
 0xFFFE, 0xD5F6, 0x5A48, 0xFF5C, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFBF, 0xFFDF, 0xFFDF, 0xFFDF,
 0x8B8A, 0xCD92, 0xFFFE, 0xFF1A, 0x62A9, 0xDE78, 0xFFBD, 0xFFFE, 0xACB0, 0x72E9, 0xFFFD, 0x93ED, 0xACD2, 0xFFFF, 0xF77D, 0xFFFF,
 0xEE98, 0x72C9, 0xF71A, 0xFFFD, 0xFFBC, 0xFFFE, 0xB4F1, 0x93ED, 0xFFFE, 0xFFDD, 0xACF1, 0x732A, 0xF71A, 0x6AE9, 0xE698, 0xFFFE,
 0xFFBE, 0xBD13, 0x72CA, 0xFFFE, 0xFF7D, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFFF, 0xF77E, 0xCE59, 0xFFBE,
 0x8B6A, 0xDDF4, 0xFF3A, 0xD5D5, 0xA4B1, 0xA4B1, 0xFFFE, 0xFFFE, 0x7B2A, 0xB512, 0xFFFE, 0x8BAC, 0x942F, 0xFFFF, 0xFFFF, 0xFFFF,
 0xEE98, 0x6AA9, 0xFF7B, 0xEED9, 0xE698, 0xFFFE, 0x942E, 0x9C2E, 0xFFFE, 0xFF5B, 0x730A, 0xC5B4, 0xFFDD, 0xA4D1, 0x942E, 0xFFFE,
 0xFF9D, 0x72A9, 0xAC91, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF77D, 0xFFFF, 0xDEDB, 0x7B8E, 0xA4F3,
 0x6266, 0xA46E, 0xACD1, 0xA470, 0xE6B9, 0x8BEE, 0xAD13, 0x9450, 0x7B6B, 0xEED9, 0xF6FA, 0x7B6B, 0x7B8D, 0xEEFA, 0xFFFF, 0xF79E,
 0xBD53, 0x5206, 0xB533, 0x9C4F, 0xACF2, 0xFF9C, 0x7B6C, 0x732B, 0xA4B1, 0x940E, 0x8BEE, 0xFF9C, 0xFFFE, 0xDE98, 0x942F, 0xAD12,
 0xB4F2, 0x7B2B, 0xFF5C, 0xFFBE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF79E, 0xFFFF, 0xFFBE, 0xAD34, 0xC5D7,
 0xD5D4, 0xCDB4, 0xC5B4, 0xBD74, 0xFFFF, 0xE6B9, 0xAD13, 0xAD33, 0xEED9, 0xFFFE, 0xF73A, 0xCDF5, 0xCDF6, 0xEF1B, 0xFFFF, 0xFFFF,
 0xE698, 0xBD74, 0xCDB5, 0xCDF6, 0xEED9, 0xFFFE, 0xDE57, 0xBD53, 0xCDF6, 0xD637, 0xFFDD, 0xFFFE, 0xFFFE, 0xFFFE, 0xF75B, 0xB553,
 0xA491, 0xEEFA, 0xFFFF, 0xFFBE, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFBF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFE, 0xFFDD, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xF77D, 0xFFFF, 0xFFFE, 0xFFFE, 0xFFDD, 0xFFFE, 0xFFFE, 0xFF9D, 0xFFFF, 0xFFFF,
 0xFFBE, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xFF9D, 0xFFFF, 0xFFBE, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFBE, 0xFF9D, 0xFFFF, 0xFFDE, 0xFFFE,
 0xFFDD, 0xFFFE, 0xFFDD, 0xFFFF, 0xFFFF, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBE, 0xFF9E, 0xFFFF, 0xE6FB,
 0xFFBD, 0xF73B, 0xFFDE, 0xFFFE, 0xEF3C, 0xF79E, 0xFFFF, 0xF75C, 0xFFBD, 0xFFDD, 0xFFFE, 0xFFFD, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFF9D, 0xFFBD, 0xFFDE, 0xFF7D, 0xFFDE, 0xF71B, 0xFF9D, 0xFFFE, 0xFFBE, 0xFF7D, 0xFFBD, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFBD, 0xFF9D,
 0xFFFE, 0xEF1B, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBE, 0xCE18,
 0xFF9D, 0xDE99, 0xC618, 0xE6DB, 0xBDD7, 0xE73D, 0xFFFF, 0xCE59, 0xDE78, 0xF73B, 0xD637, 0xDE57, 0xD637, 0xF73B, 0xDEBA, 0xEF1C,
 0xDE79, 0xC5B6, 0xD658, 0xB554, 0xDEBA, 0xD638, 0xDE99, 0xD658, 0xFFDE, 0xCE38, 0xFFFF, 0xD699, 0xF77D, 0xF77D, 0xE6DA, 0xC5D6,
 0xDED9, 0xBDB5, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7DF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xE71C, 0xDEDB,
 0xF73B, 0xCDF6, 0xB555, 0xE71B, 0xAD76, 0xFFFF, 0xFFDF, 0xCE38, 0xEEFA, 0xFFBD, 0xBD53, 0xE6B9, 0xE6DA, 0xF73B, 0xBDD6, 0xE71C,
 0xDE99, 0xD658, 0xE6BA, 0xBD75, 0xE6DA, 0xCDF7, 0xEF1B, 0xD658, 0xF77D, 0xDE79, 0xFFFF, 0xBDB6, 0xFFDE, 0xFFFF, 0xC5F7, 0xE71B,
 0xD678, 0xC617, 0xDEFA, 0xFFDE, 0xFFFF, 0xFFFF, 0xF7DF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xD6BA, 0xBDD7,
 0xE6BB, 0xCDF7, 0xD659, 0xDE7A, 0xCE38, 0xF75D, 0xFFDF, 0xD639, 0xDE9A, 0xD659, 0xD659, 0xDE79, 0xDE9A, 0xD679, 0xD659, 0xD679,
 0xD679, 0xC5F6, 0xE6FB, 0xB575, 0xEF3C, 0xC617, 0xE71B, 0xCE38, 0xDEBA, 0xC617, 0xD679, 0xCE37, 0xDEDA, 0xFFDE, 0xDEB9, 0xCE58,
 0xD6BA, 0xCE79, 0xDEDB, 0xF7BE, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF79E, 0xE73C,
 0xFFDF, 0xF75D, 0xFF9E, 0xFF9E, 0xF73C, 0xFFFF, 0xFFFF, 0xF75D, 0xFFDF, 0xFF9E, 0xFF9E, 0xFFBE, 0xFFDF, 0xFFBE, 0xFF9E, 0xFFBE,
 0xFFBE, 0xF77D, 0xFFFF, 0xEF3C, 0xFFFF, 0xF79D, 0xFFFF, 0xF79D, 0xFFBD, 0xEF3C, 0xFFBE, 0xEF5C, 0xFFBE, 0xFFFF, 0xF79D, 0xF77D,
 0xF7BE, 0xEF7D, 0xF79E, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFDE, 0xFFFF, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDE, 0xFFDE, 0xFFFF, 0xFFDE, 0xFFBE, 0xFFFF, 0xFFDE, 0xFFFF,
 0xFFDF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFDF, 0xFFFF, 0xFFDF, 0xFFFF, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xF7DF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xF7DF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7BE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBE, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFDE, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xFFBE, 0xFFFF, 0xFFFF, 0xE6FB,
 0xAD34, 0xE6FB, 0xFFFF, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBF, 0xFFFF, 0xFFFF, 0xF79E, 0xFFFF, 0xF77D, 0x9471,
 0x39A6, 0x9CD2, 0xF79D, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7FF, 0xF7FF, 0xFFFF, 0xFFFF, 0xFFBF, 0xFFBF, 0xE7BF, 0xEFFF, 0xEFFD, 0xF7FD, 0xFD92, 0x8A04,
 0xB367, 0x8202, 0xE635, 0xFFFD, 0xCFFF, 0xC7FF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFDF, 0xE7FF, 0xE7FF, 0xFFFF, 0xFFFF, 0xEFFF, 0xEFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7FF, 0xF7FF, 0xFFFF, 0xFFFF, 0xFFBF, 0xFF9F, 0xEFFF, 0xEFFF, 0xEFFD, 0xDF9B, 0xA2A6, 0xB328,
 0xC409, 0xBB88, 0x72C7, 0xFF39, 0xCFFF, 0xCFFF, 0xFFDF, 0xFFDF, 0xFFDF, 0xFFDF, 0xE7FF, 0xE7FF, 0xFFFF, 0xFFFF, 0xEFFF, 0xEFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBF, 0xFFDF, 0xFFFF, 0xFFDF, 0xFFFD, 0x940D, 0x9AC6, 0xA327,
 0x82A4, 0x9B67, 0x7A05, 0xCC8F, 0xEFFF, 0xEFFE, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xEFFF, 0xEFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xF79E, 0xFFFF, 0xD636, 0x5225, 0xBBEB, 0x8223,
 0x5940, 0x7222, 0xAB8B, 0x8A87, 0xC6B9, 0xE7DE, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xEFFF, 0xEFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7FF, 0xF7FF, 0xFFFE, 0xFFDE, 0x92E8, 0xABAB, 0x7AA4, 0x61C1,
 0x41C1, 0x4A01, 0xB2C8, 0xAA87, 0x8B8D, 0xFFDE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7DF, 0xF7FF, 0xFFFE, 0xCD95, 0x8A86, 0xB3EC, 0x5140, 0x61C1,
 0x4A02, 0x4A01, 0x8163, 0xBB2A, 0x6A89, 0xDE17, 0xFFFF, 0xF7DF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xEFFE, 0xF7FE, 0xFFBC, 0x934B, 0xC36A, 0x9A04, 0x51C0, 0x72E5,
 0x4AE5, 0x42E5, 0x8142, 0xAA87, 0x9B0A, 0xB3AD, 0xEFBD, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7FE, 0xEFFD, 0xFED9, 0x82A8, 0xBB29, 0x8142, 0x5A01, 0xA46B,
 0x8D0E, 0x7C8C, 0x8163, 0x8163, 0x9AEA, 0x9B0A, 0xD6D9, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xF7FE, 0xF7FD, 0xC4AF, 0x9B6A, 0xAAC7, 0x70E0, 0x49C1, 0x6AE5,
 0x7CEE, 0x32A5, 0x6162, 0x71C3, 0x9AC8, 0x9287, 0xA552, 0xFFFE, 0xF7FF, 0xF7FF, 0xF7FF, 0xF7FF, 0xEFFF, 0xEFFF, 0xFFFF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xF7FE, 0xF7FD, 0x9349, 0x82C7, 0x89C3, 0x89A2, 0x49E1, 0x41C1,
 0x74AD, 0x2A84, 0x5921, 0x6142, 0x8205, 0xA309, 0x7C0D, 0xF7BC, 0xF7FE, 0xF7FF, 0xF7FF, 0xF7FF, 0xEFFF, 0xEFFF, 0xFFFF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFD, 0xE6F9, 0x7285, 0x8B49, 0x5981, 0x69C2, 0x41E2, 0x5A64,
 0x4AC7, 0x4265, 0x6B48, 0x6B48, 0x7A04, 0xAB69, 0x62A6, 0xF739, 0xEFFE, 0xEFFE, 0xF7FF, 0xFFFF, 0xF7FF, 0xF7FF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFE, 0xB573, 0x7AC6, 0x82E7, 0x5981, 0x6181, 0x3960, 0x41E2,
 0x2182, 0x4265, 0x9CCE, 0xA4CE, 0x7A04, 0x9AE7, 0x5A66, 0xD635, 0xEFFE, 0xEFFE, 0xF7DF, 0xFFFF, 0xF7FF, 0xEFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7FF, 0xF7FF, 0xFFFF, 0xFFFF, 0xFFDC, 0x9BCC, 0x8369, 0x51E3, 0x5B07, 0x7BEA, 0x6AE8, 0x3982,
 0x5183, 0x5163, 0x5C2A, 0x6C8C, 0x6181, 0x7A44, 0x9B28, 0xBC4D, 0xFFFE, 0xF7FE, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF7FF, 0xF7FF, 0xFFFF, 0xFFFF, 0xFFBC, 0x7AC8, 0x8BCA, 0x62A5, 0x94AE, 0x8C8D, 0x83AB, 0x6AC7,
 0x59C4, 0x4922, 0x4BA8, 0x644B, 0x5960, 0x69C1, 0xABAB, 0x9308, 0xEFDD, 0xF7FE, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xE7FF, 0xE7FF, 0xFFFF, 0xFFFF, 0xFF1A, 0x8288, 0x7389, 0x840B, 0x646C, 0x1A23, 0x49E5, 0x730A,
 0x7123, 0x7123, 0x442A, 0x5CCD, 0x59A0, 0x59A0, 0xBB49, 0xA2A7, 0xE71A, 0xFFDD, 0xFFDF, 0xFFDF, 0xFFBF, 0xFFDF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xE7FF, 0xE7FF, 0xFFFF, 0xFFFF, 0xE594, 0x8AA8, 0x5AE6, 0x948D, 0x4BA9, 0x0160, 0x49C4, 0x838B,
 0x7123, 0x7944, 0x3C09, 0x4C8B, 0x5960, 0x61C1, 0xA286, 0xAAC7, 0xD698, 0xF7BC, 0xFFDF, 0xFFDF, 0xFFBF, 0xFFDF, 0xFFFF, 0xF7FE,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xE7FF, 0xEFFF, 0xFFDF, 0xFFDF, 0xEFFF, 0xEFFF, 0xD50F, 0x9B48, 0x3266, 0x746D, 0x7306, 0x51E1, 0x3A24, 0x6B69,
 0x51E5, 0x30E1, 0x7BAB, 0x840C, 0x49C2, 0x49C2, 0x7AA6, 0x82A6, 0xC532, 0xFFFD, 0xEFFE, 0xEFFE, 0xE7FF, 0xE7FF, 0xEFFE, 0xF7FF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xE7FF, 0xE7FF, 0xFFDF, 0xFFDF, 0xEFFF, 0xEFFF, 0xCCAD, 0x9B48, 0x3245, 0x84F0, 0x7B47, 0x49A0, 0x39E3, 0x6B89,
 0x51E5, 0x41A4, 0x7369, 0x840C, 0x4181, 0x5203, 0x7245, 0x9369, 0xB4D0, 0xFFFD, 0xF7FF, 0xEFFE, 0xE7FF, 0xE7FF, 0xF7FF, 0xF7FF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xEFFF, 0xEFFF, 0xFFFE, 0xFFFE, 0xEFFF, 0xEFDF, 0xABCB, 0x9328, 0x19A4, 0x7CB0, 0x72E7, 0x4181, 0x31E5, 0x5B2A,
 0x5369, 0x4B49, 0x4B89, 0x6C8D, 0x4AA4, 0x6368, 0x59E3, 0x8B29, 0xA40E, 0xFFFE, 0xFFFF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xEFFF, 0xEFFF, 0xFFFE, 0xFFFE, 0xEFDF, 0xE7BF, 0xA38A, 0xA3AA, 0x1983, 0x746F, 0x6AE7, 0x49C2, 0x3A46, 0x5309,
 0x640C, 0x746D, 0x640B, 0x7D0E, 0x7C2B, 0x846B, 0x59E3, 0x8B49, 0x938C, 0xFFDD, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFE, 0xFFFE, 0xF7FF, 0xF7FF, 0xFFFE, 0xFFFE, 0xF7DF, 0xE77F, 0x8B28, 0x936A, 0x21A5, 0x8470, 0x7308, 0x4161, 0x3A06, 0x634B,
 0x5A86, 0x7328, 0x6B68, 0x6B68, 0x7B47, 0x6AE5, 0x5961, 0x9B6A, 0x8B2B, 0xFFBD, 0xFFFF, 0xFFFF, 0xEFDF, 0xF7FF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFE, 0xFFFE, 0xF7FF, 0xF7DF, 0xFFFE, 0xFFFE, 0xEFBF, 0xE75E, 0x82C7, 0x8B08, 0x3A47, 0x94F2, 0x8BEB, 0x49A2, 0x4A88, 0x94B1,
 0x5224, 0x49E3, 0x4202, 0x2960, 0x4A02, 0x41A0, 0x5120, 0x9349, 0x830B, 0xFF9C, 0xFFFF, 0xFFFF, 0xEFDF, 0xF7FF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xF7DF, 0xFFFE, 0xFFFE, 0xFFBF, 0xEF3D, 0x9328, 0x9328, 0x5AA7, 0x8C2D, 0xA40A, 0x6A43, 0x72E8, 0xA48E,
 0x92C6, 0x71A1, 0x61C0, 0x5160, 0x6A01, 0x61E1, 0x69A2, 0x9B48, 0x830A, 0xFF7B, 0xF7FF, 0xF7FF, 0xE7FF, 0xE7FF, 0xF7FF, 0xF7FF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFE, 0xFFFF, 0xFFFF, 0xF7DF, 0xFFFE, 0xFFFE, 0xFFBF, 0xEF1D, 0x8B27, 0x82E6, 0x39A3, 0x3162, 0x6202, 0x5180, 0x4982, 0x49C3,
 0x79E2, 0x6120, 0x61E1, 0x61E1, 0x61C0, 0x5980, 0x6981, 0x9B07, 0x830A, 0xFF5B, 0xF7FF, 0xF7FF, 0xE7FF, 0xE7FF, 0xF7FF, 0xF7FF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xF7DF, 0xF7DF, 0xFFFE, 0xFFFE, 0xFFDF, 0xEEFC, 0x8B26, 0x8305, 0x59E3, 0x4940, 0x7200, 0x7220, 0x69C1, 0x69E1,
 0x71C1, 0x6180, 0x59C0, 0x6221, 0x61E0, 0x5980, 0x71E2, 0x92E6, 0x8AE9, 0xFF19, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFBE,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFFE, 0xFFFE, 0xFFBF, 0xEEDB, 0x9BA8, 0xB46B, 0xAC6D, 0xA40B, 0xA386, 0x7A41, 0x5960, 0x69C1,
 0x71C1, 0x71E1, 0x6A41, 0x72A3, 0x9366, 0xAC29, 0xC46C, 0xC46C, 0x82C8, 0xFF1A, 0xFFFF, 0xFFFE, 0xFFFE, 0xF7DE, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xF7FF, 0xF7FF, 0xFFDF, 0xFFDF, 0xFFFE, 0xFFFE, 0xFF9F, 0xEEDC, 0x51C1, 0x72E5, 0x7AA6, 0x7265, 0xA3C7, 0xCD0C, 0xBC2B, 0x8AA5,
 0x6940, 0x9A85, 0xB42B, 0xBC8C, 0xA3E9, 0x8B06, 0x8265, 0x7A45, 0x6226, 0xF698, 0xF7FF, 0xF7FF, 0xEFFE, 0xEFFE, 0xFFFE, 0xFFFE,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xF7FF, 0xF7FF, 0xFFDF, 0xFFDF, 0xFFFE, 0xFFFE, 0xFFBF, 0xF71D, 0x8367, 0x8BA8, 0x9B8A, 0x8B08, 0x7A62, 0x69E0, 0x8AC5, 0xBC4B,
 0xD44C, 0xCC2C, 0x9306, 0x61A1, 0x69E2, 0x9368, 0xABAA, 0x9308, 0x8B8C, 0xFED9, 0xF7FF, 0xF7FF, 0xF7FF, 0xEFFE, 0xFFFE, 0xFFFE,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xF7FE, 0xFFDF, 0xFFDF, 0xFFFE, 0xFFFF, 0xFFDF, 0xFF7F, 0xF799, 0xF799, 0xFF9D, 0xFFFE, 0xFF59, 0xBD51, 0x7AEA, 0x4985,
 0x9AA9, 0x7165, 0x7A88, 0xDDB4, 0xFFBC, 0xFF9B, 0xFF7C, 0xFFFE, 0xE6BA, 0xFFDF, 0xE7FF, 0xE7FF, 0xDFFF, 0xDFFF, 0xF7FF, 0xF7FF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xF7FE, 0xFFDF, 0xFFDF, 0xFFFE, 0xFFFF, 0xFFDF, 0xFFBF, 0xFFFB, 0xFFFC, 0xFFFE, 0xFFFE, 0xFFFC, 0xFFFC, 0xF699, 0xA42F,
 0x7165, 0xC40F, 0xFEF9, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFDD, 0xFF9C, 0xFFFF, 0xFFFF, 0xE7FF, 0xE7FF, 0xDFFF, 0xDFFF, 0xF7FE, 0xF7FF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFE, 0xFFFD, 0xFFFF, 0xFFFF, 0xF7FE, 0xFFFE, 0xFFBF, 0xFFBF, 0xF7FE, 0xEFFC, 0xF79F, 0xFFDF, 0xF7FF, 0xF7FF, 0xFFBF, 0xE6FE,
 0xAD96, 0xD6FC, 0xEFFF, 0xEFFF, 0xEFFE, 0xEFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFBF, 0xF7DF, 0xF7FF, 0xFFDF, 0xFFDF, 0xFFBF, 0xFFBF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFE, 0xFFFD, 0xFFFF, 0xFFFF, 0xFFFE, 0xF7FE, 0xFFBF, 0xFF9F, 0xF7FE, 0xF7FD, 0xFFDF, 0xFFDF, 0xEFDE, 0xF7FF, 0xFFBF, 0xF79F,
 0xF7FF, 0xF7FF, 0xEFFF, 0xEFFF, 0xEFFF, 0xEFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xF7FF, 0xEFBF, 0xFFBF, 0xFFDF, 0xFFDF, 0xFFDF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
};

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
