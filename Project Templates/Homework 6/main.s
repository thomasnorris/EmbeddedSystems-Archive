;*******************************************************************
; main.s
; Author: Thomas Norris
; Date Created: 10/14/19
; Last Modified: 10/14/19
; Section Number: 003
; Instructor: Gursel Serpen
; Homework Number: 6
; Brief description of the program
;	Program for HW6 - Question 3
;*******************************************************************

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
	MOV r0, #13          ; store the age in r0

MoviePrice
	CMP r0, #12
	MOVLE r0, #6         ; ticket price is $6 for those ages 12 and under, store in r0 and exit
	BLE loop
	
	CMP r0, #65
	MOVGE r0, #7         ; ticket price is $7 for those ages 65 or over, store in r0 and exit
	BGE loop
	
	MOV r0, #8           ; ticket price is $8 for all other ages, store in r0 and exit

loop
	; forever
	B    loop


	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
