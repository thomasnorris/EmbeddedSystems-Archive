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
	MOV r0, #0                      ; r0 will hold the sum of the array, initialize to 0
	MOV r1, #0                      ; r1 will hold the current index of the array, initialize to 0
	LDR r2, =intArr                 ; load r2 with the base address of intArr
	LDR r3, intArrLength            ; set r3 to intArrLength
	
	SUB r3, r3, #1                  ; subtract 1 from r3 so r3 = intArrLength - 1 

forLoop
	CMP r1, r3                      ; compare r1 with r3
	BGT loop                        ; if r1 > r3 (i.e. the current index is greater than intArrLength - 1), exit forLoop

	PUSH {r4}                       ; we need r4, push it to the stack

	LDR r4, [r2], #4                ; load the current value of r2 into r4 and shift r2 by 4 for the next iteration
	ADD r0, r0, r4                  ; add r4 to the running sum in r0
	ADD r1, r1, #1                  ; add 1 to the current array index in r1

	POP {r4}                        ; pop r4 from the stack

	B forLoop                       ; repeat forLoop

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
