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
	; note: the test value can be any 8-digit hex value, not just what's here. I used
	;       0x12345678 when writing the instructions but that value is too big to be executed
	;       on the controller.

	MOV r1, #0x00110011     ; 32 bit test value
	MOV r0, r1, LSL #24     ; r0 = 0x11000000

	MOV r2, #8
	MOV r3, #24
	BL chopAndShift         ; r0 = 0x11000000 after execution

	MOV r2, #16
	MOV r3, #24
	BL chopAndShift         ; r0 = 0x11001100 after execution

	MOV r3, r1, LSR #24     ; r3 = 0x00000000
	ORR r0, r0, r3          ; r0 = 0x11001100

	B loop                  ; branch (without link) to forever loop

chopAndShift
	; r0, r1, r2, r3 are parameters
	; r4 is a local variable
	; returns in r0
	
	PUSH {r4}               ; push r4 onto the stack

	MOV r4, r1, LSR r2      ; chop right r2 bits off r1, store in r4
	MOV r4, r4, LSL r3      ; chop left r3 bits off r4, store in r4
	MOV r4, r4, LSR r2      ; shift r4 right by r2 bits, store in r4

	ORR r0, r0, r4          ; bitwise OR r4 byte with r0
	
	POP {r4}                ; pop r4 from the stack
	
	BX LR                   ; branch back to the link register

loop
	; forever
	B    loop


       ALIGN      ; make sure the end of this section is aligned
       END        ; end of file
