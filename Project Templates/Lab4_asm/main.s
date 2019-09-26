;*******************************************************************
; main.s
; Author: Thomas Norris
; Date Created: 9/25/19
; Last Modified: 9/25/19
; Section Number: 003
; Instructor: Gursel Serpen
; Lab number: 4
;   Brief description of the program
; The overall objective of this system is an interactive alarm
; Hardware connections
;   PF4 is switch input  (1 = switch not pressed, 0 = switch pressed)
;   PF3 is LED output    (1 activates green LED)
; The specific operation of this system
;   1) Make PF3 an output and make PF4 an input (enable PUR for PF4).
;   2) The system starts with the LED OFF (make PF3 =0).
;   3) Delay for about 100 ms
;   4) If the switch is pressed (PF4 is 0),
;      then toggle the LED once, else turn the LED OFF.
;   5) Repeat steps 3 and 4 over and over
;*******************************************************************

GPIO_PORTF_DATA_R       EQU   0x400253FC
GPIO_PORTF_DIR_R        EQU   0x40025400
GPIO_PORTF_AFSEL_R      EQU   0x40025420
GPIO_PORTF_PUR_R        EQU   0x40025510
GPIO_PORTF_DEN_R        EQU   0x4002551C
GPIO_PORTF_AMSEL_R      EQU   0x40025528
GPIO_PORTF_PCTL_R       EQU   0x4002552C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608
GPIO_PORTF_LOCK_R  	    EQU   0x40025520
GPIO_PORTF_CR_R         EQU   0x40025524

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
	; port F initialization
	; enable the clock for port F
	LDR r1, =SYSCTL_RCGCGPIO_R
	LDR r0, [r1]
	ORR r0, r0, #0x20
	STR r0, [r1]

	; set PF3 as output (1), PF4 as input (0)
	LDR r1, =GPIO_PORTF_DIR_R
	MOV r0, #0x08
	STR r0, [r1]

	; enable PF3 and PF4
	LDR r1, =GPIO_PORTF_DEN_R
	MOV r0, #0x18
	STR r0, [r1]

	; set PUR for PF4
	LDR r1, =GPIO_PORTF_PUR_R
	MOV r0, #0x10
	STR r0, [r1]

	; set PF3 to off
	LDR r1, =GPIO_PORTF_DATA_R
	MOV r0, #0x00
	STR r0, [r1]

	; fall through to main

main
	; delay by ~100ms
	B delay

afterDelay
	; read the value of PF4
	LDR r1, =GPIO_PORTF_DATA_R
	LDR r0, [r1]
	AND r2, r0, #0x10

	; if PF3 is 0 (switch is pressed), toggle the LED
	CMP r2, #0x00
	BEQ toggleLed

	; else PF3 is 1 (switch is not pressed), turn off the LED
	MOV r0, #0x00
	STR r0, [r1]

	; loop forever
	B main

toggleLed
	; flip PF4 and write to the register
	EOR r0, r0, #0x08
	STR r0, [r1]

	B main

delay
	; outerLoop will be called r0 times, innerLoop will be called r1 times
	MOV r0, #10
	MOV r1, #40000

outerLoop
	; move r1 into r2 so r1 is not overwritten
	MOV r2, r1

	; subtract 1 from r0, if not 0, go to innerLoop, otherwise the delay is done
	SUBS r0, r0, #0x01
	CMP r0, #0x00
	BNE innerLoop

	B afterDelay

innerLoop
	; subtract 1 from r2, if not 0, repeat innerLoop, otherwise go back to outerLoop
	SUBS r2, r2, #0x01
	CMP r2, #0x00;
	BNE innerLoop

	B outerLoop

	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file