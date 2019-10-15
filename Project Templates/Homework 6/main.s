;*******************************************************************
; main.s
; Author: Thomas Norris
; Date Created: 10/14/19
; Last Modified: 10/14/19
; Section Number: 003
; Instructor: Gursel Serpen
; Homework Number: 6
; Brief description of the program
;	Program for HW6 - Question 1
;*******************************************************************

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
	; use registers r0 to r3 for first 4 numbers
	MOV r0, #1
	MOV r1, #2
	MOV r2, #3
	MOV r3, #4

	; push last 4 numbers to the stack
	MOV r4, #5
	PUSH {r4}
	MOV r4, #6
	PUSH {r4}
	MOV r4, #7
	PUSH {r4}
	MOV r4, #8
	PUSH {r4}

	; call subroutine
	BL ComputeSum

	; do something with the sum in r0
	
	; branch to forever loop
	B loop

ComputeSum
	; sum first 4 numbers and store in r0
	ADD r0, r0, r1
	ADD r0, r0, r2
	ADD r0, r0, r3

	; load and sum last 4 numbers from the stack and store in r0
	POP {r4}
	ADD r0, r0, r4
	POP {r4}
	ADD r0, r0, r4
	POP {r4}
	ADD r0, r0, r4
	POP {r4}
	ADD r0, r0, r4

	; r0 contains the sum (0x24)
	BX LR

loop
	; forever
	B    loop


	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
