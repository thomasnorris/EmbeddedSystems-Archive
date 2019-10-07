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
	MOV r0, #0             ; r0 will be the result
	MOV r1, #-4            ; signed int to raise to a power
	MOV r2, #3             ; the unsigned power which to raise r1

	MOV r0, r1             ; move r1 into r0 (same as multiplying r1 by 1)

multiply
	CMP r2, #1             ; if r2 = 1, we are done, go to loop
	BEQ loop
	
	MUL r0, r0, r1         ; multiply r0 by r1 and place in r0
	SUB r2, r2, #1         ; subtract 1 from r2
	B multiply             ; do the multiplication again

loop   
	; forever
	B    loop


       ALIGN      ; make sure the end of this section is aligned
       END        ; end of file
       