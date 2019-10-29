; Program written by: Thomas Norris
; Date Created: 10/27/19
; Last Modified: 10/27/19
; Lab Section: 003
; Lab Instructor: Gursel Serpen
; Homework Number: 7 - Question 8


	AREA subroutine, CODE
	ALIGN

; r0 = int1
; r1 = int2
; r2 = int3
; r3 = int4
; r4 = max
max4 PROC
	EXPORT max4
	
	PUSH {r4}       ; need r4, push it
	
	MOV r4, #0      ; set max to 0 
	
	CMP r0, r4      ; if r0 >= r4, r4 = r0
	MOVGE r4, r0
	
	CMP r1, r4      ; same process until r4 is the max
	MOVGE r4, r1
	
	CMP r2, r4
	MOVGE r4, r2
	
	CMP r3, r4
	MOVGE r4, r3
	
	MOV r0, r4      ; move r4 into r0
	
	POP {r4}        ; pop r4

	BX LR           ; return
	
	ENDP
	END