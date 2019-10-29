; Program written by: Thomas Norris
; Date Created: 10/27/19
; Last Modified: 10/27/19
; Lab Section: 003
; Lab Instructor: Gursel Serpen
; Homework Number: 7 - Question 7


	AREA subroutine, CODE
	ALIGN

; r0 = *str1
; r1 = *str2
Swap PROC
	EXPORT Swap

	LDR r2, [r0]
	LDR r3, [r1]
	STR r2, [r1]
	STR r3, [r0]
	
	BX LR
	
	ENDP
	END