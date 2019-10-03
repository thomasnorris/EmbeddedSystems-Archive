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
	; do stuff, fall to loop

loop   
	; do more stuff
	B    loop


       ALIGN      ; make sure the end of this section is aligned
       END        ; end of file
       