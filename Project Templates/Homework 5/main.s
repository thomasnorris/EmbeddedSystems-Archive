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
	; do stuff
	; not tested
	; question 1
	MOV r1, #0x12345678     ; 32 bit test value
	MOV r0, r1, LSL #24     ; r0 = 0x78000000

	MOV r2, r1, LSR #8      ; r2 = 0x00123456
	MOV r2, r2, LSL #24     ; r2 = 0x56000000
	MOV r2, r2, LSR #8      ; r2 = 0x00560000

	ORR r0, r0, r2          ; r0 = 0x78560000

loop
	; forever
	B    loop


       ALIGN      ; make sure the end of this section is aligned
       END        ; end of file
