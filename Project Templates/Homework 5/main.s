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
	MOV r0, #0               ; r0 will be f(x)
	MOV r1, #-78             ; r1 is the test value
	
	CMP r1, #0x00            ; compare r1 to #0x00, branch accordingly
	BLT lessThanZero
	BEQ equalToZero
	BGT greaterThanZero
	
lessThanZero
	MOV r0, #-1              ; f(x) = -1
	B loop

equalToZero
	MOV r0, #0               ; f(x) = 0
	B loop

greaterThanZero
	MOV r0, #1               ; f(x) = 1
	B loop

loop   
	; forever
	B    loop


       ALIGN      ; make sure the end of this section is aligned
       END        ; end of file
       