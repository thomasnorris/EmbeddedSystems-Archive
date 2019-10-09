;*******************************************************************
; main.s
; Author: ***update this***
; Date Created: 11/18/2016
; Last Modified: 11/18/2016
; Section Number: ***update this***
; Instructor: ***update this***
; Lab number: 5
; Brief description of the program
;   If the switch is presses, the LED toggles at 8 Hz
; Hardware connections
;  PE1 is switch input  (1 means pressed, 0 means not pressed)
;  PE0 is LED output (1 activates external LED on protoboard) 
; Overall functionality is similar to Lab 4, with six changes:
;   1) the pin to which we connect the switch is moved to PE1, 
;   2) you will have to remove the PUR initialization because
;      pull up is no longer needed. 
;   3) the pin to which we connect the LED is moved to PE0, 
;   4) the switch is changed from negative to positive logic, and 
;   5) you should increase the delay so it flashes about 8 Hz.
;   6) the LED should be on when the switch is not pressed
; Operation
;   1) Make PE0 an output and make PE1 an input. 
;   2) The system starts with the LED on (make PE0 =1). 
;   3) Wait about 62 ms
;   4) If the switch is pressed (PE1 is 1), then toggle the LED
;      once, else turn the LED on. 
;   5) Steps 3 and 4 are repeated over and over
;*******************************************************************

GPIO_PORTE_DATA_R       EQU   0x400243FC
GPIO_PORTE_DIR_R        EQU   0x40024400
GPIO_PORTE_AFSEL_R      EQU   0x40024420
GPIO_PORTE_DEN_R        EQU   0x4002451C
GPIO_PORTE_AMSEL_R      EQU   0x40024528
GPIO_PORTE_PCTL_R       EQU   0x4002452C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608
	
	IMPORT  TExaS_Init

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
	; TExaS_Init sets bus clock at 80 MHz
	BL  TExaS_Init

	; port E initialization
	; enable the clock for port E
	LDR r1, =SYSCTL_RCGCGPIO_R
	LDR r0, [r1]
	ORR r0, r0, #0x10
	STR r0, [r1]
	
	; allow time for the clock to activate
	NOP
	NOP

	; set PE0 as output (1), PE1 as input (0)
	LDR r1, =GPIO_PORTE_DIR_R
	MOV r0, #0x01
	STR r0, [r1]

	; enable PE0 and PE1
	LDR r1, =GPIO_PORTE_DEN_R
	MOV r0, #0x03
	STR r0, [r1]

	; set PE0 to ON
	LDR r1, =GPIO_PORTE_DATA_R
	MOV r0, #0x01
	STR r0, [r1]

	; TExaS voltmeter, scope runs on interrupts
	CPSIE  I

main
	; delay by ~62ms
	BL delay
	
	; read the value of PE1
	LDR r1, =GPIO_PORTE_DATA_R
	LDR r0, [r1]
	AND r2, r0, #0x02

	; if PE1 is 1 (switch is pressed), toggle the LED
	CMP r2, #0x02
	BEQ toggleLed

	; else PE1 is 0 (switch is not pressed), turn on the LED
	MOV r0, #0x01
	STR r0, [r1]

	; loop forever
	B main

toggleLed
	; flip PE0 and write to the register
	EOR r0, r0, #0x01
	STR r0, [r1]

	B main

delay
	; outerLoop will be called r0 times, innerLoop will be called r1 times
	MOV r0, #35
	MOV r1, #30000

outerLoop
	; move r1 into r2 so r1 is not overwritten
	MOV r2, r1

	; subtract 1 from r0, if not 0, go to innerLoop, otherwise the delay is done
	SUBS r0, r0, #0x01
	CMP r0, #0x00
	BNE innerLoop
	
	; exit the delay subroutine
	BX LR

innerLoop
	; subtract 1 from r2, if not 0, repeat innerLoop, otherwise go back to outerLoop
	SUBS r2, r2, #0x01
	CMP r2, #0x00;
	BNE innerLoop

	B outerLoop
	
	; end of program
	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
       