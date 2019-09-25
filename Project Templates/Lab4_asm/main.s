;*******************************************************************
; main.s
; Author: Thomas Norris
; Date Created: 9/25/19
; Last Modified: 9/25/19
; Section Number: 003
; Instructor: Gursel Serpen
; Lab number: 4
;   Brief description of the program
; The overall objective of this system is an interactive alarm
; Hardware connections
;   PF4 is switch input  (1 = switch not pressed, 0 = switch pressed)
;   PF3 is LED output    (1 activates green LED) 
; The specific operation of this system 
;   1) Make PF3 an output and make PF4 an input (enable PUR for PF4). 
;   2) The system starts with the LED OFF (make PF3 =0). 
;   3) Delay for about 100 ms
;   4) If the switch is pressed (PF4 is 0),
;      then toggle the LED once, else turn the LED OFF. 
;   5) Repeat steps 3 and 4 over and over
;*******************************************************************

GPIO_PORTF_DATA_R       EQU   0x400253FC
GPIO_PORTF_DIR_R        EQU   0x40025400
GPIO_PORTF_AFSEL_R      EQU   0x40025420
GPIO_PORTF_PUR_R        EQU   0x40025510
GPIO_PORTF_DEN_R        EQU   0x4002551C
GPIO_PORTF_AMSEL_R      EQU   0x40025528
GPIO_PORTF_PCTL_R       EQU   0x4002552C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608
GPIO_PORTF_LOCK_R  	    EQU   0x40025520
GPIO_PORTF_CR_R         EQU   0x40025524

       AREA    |.text|, CODE, READONLY, ALIGN=2
       THUMB
       EXPORT  Start
Start

loop  

       B    loop


       ALIGN      ; make sure the end of this section is aligned
       END        ; end of file
       