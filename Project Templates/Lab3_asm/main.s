;*******************************************************************
; main.s
; Author: ***update this***
; Date Created: 11/18/2016
; Last Modified: 11/18/2016
; Section Number: ***update this***
; Instructor: ***update this***
; Lab number: 3
; Brief description of the program
; The overall objective of this system is a digital lock
; Hardware connections
;   PE3 is switch input  (1 = switch not pressed, 0 = switch pressed)
;   PE4 is switch input  (1 = switch not pressed, 0 = switch pressed)
;   PE5 is switch input  (1 = switch not pressed, 0 = switch pressed)
;   PE2 is LED output    (0 = door locked, 1 = door unlocked) 
; The specific operation of this system is to unlock if all three
; switches are pressed
;*******************************************************************

GPIO_PORTE_DATA_R       EQU   0x400243FC
GPIO_PORTE_DIR_R        EQU   0x40024400
GPIO_PORTE_AFSEL_R      EQU   0x40024420
GPIO_PORTE_DEN_R        EQU   0x4002451C
GPIO_PORTE_AMSEL_R      EQU   0x40024528
GPIO_PORTE_PCTL_R       EQU   0x4002452C
SYSCTL_RCGCGPIO_R       EQU   0x400FE608

      AREA    |.text|, CODE, READONLY, ALIGN=2
      THUMB
      EXPORT  Start
Start

loop

	  B   loop


      ALIGN        ; make sure the end of this section is aligned
      END          ; end of file