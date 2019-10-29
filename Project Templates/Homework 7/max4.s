; Program written by: Thomas Norris
; Date Created: 10/27/19
; Last Modified: 10/27/19
; Lab Section: 003
; Lab Instructor: Gursel Serpen
; Homework Number: 7 - Question 8


	AREA subroutine, CODE
	ALIGN

; r0 = *str
; r1 = char to remove from str
; r3 will contain the new string before returning in r0
; note: expecting str to be null-terminated
max4 PROC
	EXPORT max4
		
	BX LR
	
	ENDP
	END