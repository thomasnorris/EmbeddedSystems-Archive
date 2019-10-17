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
	LDR r0, firstNum               ; store the first number in r0
	LDR r1, secondNum              ; store the second numebr in r1
	
CalcHammingDistance
	PUSH {r4}                      ; need r4 as an intermediate variable
	
	EOR r4, r0, r1                 ; bitwise XOR r0 and r1 and store in r4
	MOV r0, r4                     ; r4 contains the hamming distance, move to r0 and exit

loop
	; forever
	BL    loop


	AREA    |.text|, DATA, READONLY, ALIGN=2

firstNum
	DCD 0xFFFFFFFF                 ; 32 1's
secondNum
	DCD 0xFFFFFFFE                 ; 31 1's


	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
