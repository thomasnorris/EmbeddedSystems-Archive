	
	AREA subroutine, CODE
	ALIGN

; r0 = *str
; r1 = char to remove from str
removeAllChar PROC
	EXPORT removeAllChar
loop

	BX LR
	
	ENDP
	END