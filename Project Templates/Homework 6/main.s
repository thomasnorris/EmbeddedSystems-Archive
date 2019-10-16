;*******************************************************************
; main.s
; Author: Thomas Norris
; Date Created: 10/14/19
; Last Modified: 10/14/19
; Section Number: 003
; Instructor: Gursel Serpen
; Homework Number: 6
; Brief description of the program
;	Program for HW6 - Question 4
;*******************************************************************

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start

Start
	LDR r0, num            ; load the 32 bit number into r0 
	MOV r1, #0             ; r1 will be a counter to count how many bits we have checked
	MOV r2, #0             ; r2 will be a counter to count how many bits are 1
	
FindAllOnes
	CMP r1, #32            ; if we have checked all 32 bits
	MOVEQ r0, r2           ; move r2 into r0 and exit
	BEQ loop
	
	PUSH {r4}              ; need r4 as intermediate variable, push to stack
	
	AND r4, r0, #0x01      ; bitwise AND r0 and 0x01 to check the LSB, store in r4
	CMP r4, #0x01          ; compare r4 and 0x01
	ADDEQ r2, r2, #1       ; if r4 = 1, we know there is a 1 in the LSB, add 1 to the other counter
	ADD r1, r1, #1         ; add 1 to the check counter
	LSR r0, #1             ; shift r0 to the right by 1 bit to set the next LSB
	
	BL FindAllOnes         ; repeat (I used BL here because I get error A1875E on line 18 if I don't, why is that?)
	
loop
	; forever
	B    loop
	
	AREA    |.text|, DATA, READONLY, ALIGN=2

num
	DCD 0xFFFFEFFF         ; contains 31 1s

	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
