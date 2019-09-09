;*******************************************************************
; IO.s
; Instructor: ***fill this in***
; Student: ***fill this in***
; Section: ***fill this in***
; Date:    ***fill this in***
; Runs on LM4F120/TM4C123
;
; EECS3100 lab 9 device driver for the switch and LED.
; You are allowed to use any switch and any LED,
; although the Lab suggests the SW1 switch PF4 and Red LED PF1
;
; As part of Lab 9, students need to implement these three functions
;
; Hardware breakpoint switch connected to PE0 on the Launchpad
; LED connected to PE3 on the Launchpad
;*******************************************************************

        EXPORT   IO_Init
        EXPORT   IO_Touch
        EXPORT   IO_HeartBeat
		IMPORT   Delay1ms

GPIO_LOCK_KEY      EQU 0x4C4F434B
GPIO_PORTE_DATA_R  EQU 0x400243FC
GPIO_PORTE_DIR_R   EQU 0x40024400
GPIO_PORTE_AFSEL_R EQU 0x40024420
GPIO_PORTE_PUR_R   EQU 0x40024510
GPIO_PORTE_DEN_R   EQU 0x4002451C
GPIO_PORTE_LOCK_R  EQU 0x40024520
GPIO_PORTE_CR_R    EQU 0x40024524
GPIO_PORTE_AMSEL_R EQU 0x40024528
GPIO_PORTE_PCTL_R  EQU 0x4002452C
SYSCTL_RCGCGPIO_R  EQU 0x400FE608
    
        AREA    |.text|, CODE, READONLY, ALIGN=2
        THUMB



;------------IO_Init------------
; Initialize GPIO Port for three switches PE0-2 (without pullup) and an LED (PE3)
; This function should not interfere with PLL settings on the clock
; Input: none
; Output: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
IO_Init
    
    BX  LR
;* * * * * * * * End of IO_Init * * * * * * * *

;------------IO_HeartBeat------------
; Toggle the output state of the LED.
; Input: none
; Output: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
IO_HeartBeat

    BX  LR                        ; return
;* * * * * * * * End of IO_HeartBeat * * * * * * * *

;------------IO_Touch------------
; Hardware breakpoint
; First: wait while switch is pressed
; and then: wait until switch is released
; Input: none
; Input: none
; Output: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
IO_Touch

    BX  LR                          ; return*/
;* * * * * * * * End of IO_Touch * * * * * * * *

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file