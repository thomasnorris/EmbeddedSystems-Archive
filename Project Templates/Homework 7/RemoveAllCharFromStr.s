	
	AREA subroutine, CODE
	ALIGN

; r0 = *str
; r1 = char to remove from str
; note: expecting str to be null-terminated
; r3 will contain the new string before returning in r0
removeAllChar PROC
	EXPORT removeAllChar
loop
	LDRB r2, [r0], #1   ; load r2 with hex value of char and increment r0 address
	CMP r2, #0x00       ; compare r2 with the null terminator, end if so
	BEQ end
		
	CMP r2, r1          ; compare r2 with the value to be removed in r1
	BNE add             ; add it to the new str in r3 if not equal
	
	B loop

add
	STRB r2, [r3], #1   ; store r2 into r3, increment r3 address
	B loop

end
	MOV r0, r3          ; move r3 back into r0 and return
	BX LR
	
	ENDP
	END