;*******************************************************************
; main.s
; Author: Thomas Norris
; Date Created: 10/14/19
; Last Modified: 10/14/19
; Section Number: 003
; Instructor: Gursel Serpen
; Homework Number: 6
; Brief description of the program
;	Program for HW6
;*******************************************************************

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
	; use registers r0 to r3 for first 4 parameters
	MOV r0, #1
	MOV r1, #2
	MOV r2, #3
	MOV r3, #4

	; push last 6 numbers to the stack

	; call subroutine
	BL ComputeSum

	; do something with the sum in r0

	B loop

ComputeSum
	; sum all 10 numbers are return

	BX LR

loop
	; forever
	B    loop


	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
