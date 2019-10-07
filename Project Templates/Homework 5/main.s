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
	MOV r0, #0               ; r0 will be the result
	MOV r1, #9               ; r1 = a
	MOV r2, #10              ; r2 = b
	MOV r3, #11              ; r3 = c

aLessThanB
	CMP r1, r2               ; check a < b
	BLT aLessThanC           ; if true, go to aLessThanC
	B bLessThanA             ; if not, go to bLessThanA
	
aLessThanC
	CMP r1, r3               ; check a < c
	MOVLT r0, r1             ; if true, the min is a (r1), set r0 and exit to loop
	BLT loop
	
bLessThanA
	CMP r2, r1               ; check b < a
	BLT bLessThanC           ; if true, go to bLessThanC
	MOV r0, r3               ; if not, the min is c (r3), set r0 and exit to loop
	
bLessThanC
	CMP r2, r3               ; check b < c
	MOVLT r0, r2             ; if true, the min is b (r2), set r0 and exit to loop
	BLT loop

loop   
	; forever
	B    loop


       ALIGN      ; make sure the end of this section is aligned
       END        ; end of file
       