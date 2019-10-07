;*******************************************************************
; main.s
; Author: Thomas Norris
; Date Created: 10/3/19
; Last Modified: 10/3/19
; Section Number: 003
; Instructor: Gursel Serpen
; Homework Number: 5
; Brief description of the program
;	Program for HW5
;*******************************************************************

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
	; untested
	LDR r1, intArrLength
	SUB r1, r1, intArrLength        ; r1 = intArrLength - 1
	MOV r2, #0                      ; r2 will hold the sum of the array, initialize to 0
	MOV r3, #0                      ; r3 will hold the current index of the array, initialize to 0
	LDR r0, =intArr                 ; load r0 with the base address of intArr

forLoop
	CMP r3, r1                      ; compare r1 with r3
	BGT loop                        ; if r3 > r1 (i.e. the current index is greater than intArrLength - 1), we are done

	PUSH {r4}                       ; we need r4, push it to the stack

	; TODO: Code here

	POP {r4}                        ; pop r4 from the stack

	B forLoop

loop
	; forever
	B    loop

	AREA	|.text|, DATA, READONLY, ALIGN=2

intArr
	DCD 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
intArrLength
	DCD 10

	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
