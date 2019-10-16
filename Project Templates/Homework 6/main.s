;*******************************************************************
; main.s
; Author: Thomas Norris
; Date Created: 10/14/19
; Last Modified: 10/14/19
; Section Number: 003
; Instructor: Gursel Serpen
; Homework Number: 6
; Brief description of the program
;	Program for HW6 - Question 2
;*******************************************************************

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
	LDR r0, =strToProcess     ; load the address of the string into r0
	LDR r1, strLen            ; load the length of the string into r1
	MOV r2, #0                ; r2 will be the index counter, initialize to 0
	MOV r3, #3                ; load the shift amount into r3

CaesarShift
	ADD r2, r2, #1            ; increment index counter
	PUSH {r4, r5}             ; need r4 and r5, push to the stack
	
	LDRB r4, [r0]             ; load the ascii value of the next byte
	ADD r4, r4, r3            ; add r3 to r4 to get the next ascii value
	STRB r4, [r0]             ; store the byte in r4 back into r0 at the address
	LDR r5, [r0], #1          ; increment r0 address by 1 byte (r5 gets thrown away)
	
	POP {r4, r5}              ; pop r4 and r5
	
	CMP r2, r1                ; compare r2 and r1
	BNE CaesarShift           ; branch only if the entire string has been processed
	
	; data at address at r0 will contain the shifted string

loop
	; forever
	B    loop

	AREA    |.text|, DATA, READONLY, ALIGN=2
		

strLen
	DCD 8
strToProcess
	DCB "shift me",0
	
	
	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
