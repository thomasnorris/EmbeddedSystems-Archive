;*******************************************************************
; main.s
; Author: Thomas Norris, Juliette Ulman
; Date Created: 10/20/19
; Last Modified: 10/20/19
; Section Number: 003
; Instructor: Gursel Serpen
; Lab number: 6
; Brief description of the program
;   If the switch is presses, the LED toggles at 8 Hz
; Hardware connections
;   PE1 is switch input  (1 means pressed, 0 means not pressed)
;   PE0 is LED output (1 activates external LED on protoboard)
; Overall functionality is similar to Lab 5, with three changes:
;   1) Initialize SysTick with RELOAD 0x00FFFFFF
;   2) Add a heartbeat to PF2 that toggles every time through main
;   3) Add debugging dump of input, output, and time
; Operation
;	1) Make PE0 an output and make PE1 an input.
;	2) The system starts with the LED on (make PE0 =1)
;   3) Wait about 62 ms
;   4) If the switch is pressed (PE1 is 1), then toggle the LED
;      once, else turn the LED on.
;   5) Steps 3 and 4 are repeated over and over
;*******************************************************************

LED                     EQU 0x40024004  ;PE0
SWITCH                  EQU 0x40024008  ;PE1
SYSCTL_RCGCGPIO_R       EQU 0x400FE608
SYSCTL_RCGC2_GPIOE      EQU 0x00000010  ;port E Clock Gating Control
SYSCTL_RCGC2_GPIOF      EQU 0x00000020  ;port F Clock Gating Control
GPIO_PORTE_DATA_R       EQU 0x400243FC
GPIO_PORTE_DIR_R        EQU 0x40024400
GPIO_PORTE_AFSEL_R      EQU 0x40024420
GPIO_PORTE_PUR_R        EQU 0x40024510
GPIO_PORTE_DEN_R        EQU 0x4002451C
GPIO_PORTF_DATA_R       EQU 0x400253FC
GPIO_PORTF_DIR_R        EQU 0x40025400
GPIO_PORTF_AFSEL_R      EQU 0x40025420
GPIO_PORTF_PUR_R        EQU 0x40025510
GPIO_PORTF_DEN_R        EQU 0x4002551C
GPIO_PORTF_AMSEL_R      EQU 0x40025528
GPIO_PORTF_PCTL_R       EQU 0x4002552C
GPIO_PORTF_LOCK_R  	    EQU 0x40025520
GPIO_PORTF_CR_R         EQU 0x40025524
NVIC_ST_CTRL_R          EQU 0xE000E010
NVIC_ST_RELOAD_R        EQU 0xE000E014
NVIC_ST_CURRENT_R       EQU 0xE000E018
GPIO_PORTE_AMSEL_R      EQU 0x40024528
GPIO_PORTE_PCTL_R       EQU 0x4002452C


	AREA    DATA, ALIGN=4
	THUMB


SIZE       EQU    50
; You MUST use these two buffers and two variables
; You MUST not change their names
DataBuffer
	SPACE  SIZE*4
TimeBuffer
	SPACE  SIZE*4
DataPt
	SPACE  4
TimePt
	SPACE  4

	; These names MUST be exported
	EXPORT DataBuffer
	EXPORT TimeBuffer
	EXPORT DataPt [DATA,SIZE=4]
	EXPORT TimePt [DATA,SIZE=4]

	ALIGN


	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	EXPORT  Start
	IMPORT  TExaS_Init
	IMPORT  SysTick_Init


Start
	BL TExaS_Init  ; running at 80 MHz, scope voltmeter on PD3
	; initialize port E
	BL portEInit
	; initialize port F
	BL portFInit
	; initialize debugging dump, including SysTick
	BL debugInit
	
	CPSIE  I    ; TExaS voltmeter, scope runs on interrupts

main
	; heartbeat
	BL heartbeat
		
	; capture PE0 and PE1
	BL debugCapture
		
	; delay by ~62ms
	BL delay
	
	; store r0 - r3
	PUSH {r0, r1, r2, r3}
	
	; read the value of PE1
	LDR r1, =GPIO_PORTE_DATA_R
	LDR r0, [r1]
	AND r2, r0, #0x02

	; if PE1 is 1 (switch is pressed), toggle the LED
	CMP r2, #0x02
	BEQ toggleLed

	; else PE1 is 0 (switch is not pressed), turn on the LED
	MOV r0, #0x01
	STR r0, [r1]
	
	POP {r0, r1, r2, r3}
	
	B main
	
toggleLed
	; flip PE0 and write to the register
	EOR r0, r0, #0x01
	STR r0, [r1]
	
	POP {r0, r1, r2, r3}
	
	B main


;------------delay------------
; Toggle PF2 as a heartbeat
delay
	; store r0 - r3
	PUSH {r0, r1, r2, r3}

	; delayOuterLoop will be called r0 times, delayInnerLoop will be called r1 times
	MOV r0, #35
	MOV r1, #30000

delayOuterLoop
	; move r1 into r2 so r1 is not overwritten
	MOV r2, r1

	; subtract 1 from r0, if not 0, go to delayInnerLoop, otherwise the delay is done
	SUBS r0, r0, #0x01
	CMP r0, #0x00
	BNE delayInnerLoop
	
	POP {r0, r1, r2, r3}
		
	; exit the delay subroutine
	BX LR

delayInnerLoop
	; subtract 1 from r2, if not 0, repeat delayInnerLoop, otherwise go back to delayOuterLoop
	SUBS r2, r2, #0x01
	CMP r2, #0x00;
	BNE delayInnerLoop

	B delayOuterLoop


;------------heartbeat------------
; Toggle PF2 as a heartbeat
heartbeat
	; store r0 - r3
	PUSH {r0, r1, r2, r3}
	
	; flip PF2
	LDR r0, =GPIO_PORTF_DATA_R
	LDR r1, [r0]
	EOR r1, r1, #0x04
	STR r1, [r0]
	
	POP {r0, r1, r2, r3}
	
	BX LR

;------------debugInit------------
; Initializes the debugging instrument
debugInit
	; set DataBuffer and TimeBuffer to 0xFFFFFFFF
	LDR r0, =DataBuffer
	LDR r1, =TimeBuffer
	MOV r2, #0xFFFFFFFF
	STR r2, [r0]
	STR r2, [r1]

	; initialize pointers to the beginning address of DataBuffer and TimeBuffer
	LDR r2, =DataPt
	LDR r3, =TimePt
	STR r0, [r2]
	STR r1, [r3]

	; preserve registers
	PUSH {r0, r1, r2, r3, LR, r4}

	; init SysTick
	BL SysTick_Init

	; restore registers
	POP {r0, r1, r2, r3, LR, r4}

	BX LR

;------------debugCapture------------
; Dump Port E values and time into buffers
debugCapture
	; r0 = DataBuffer address
	; r1 = TimeBuffer address
	; r2 = DataPt address
	; r9 = DataPt value
	; r3 = TimePt address
	; r10 = TimePt value
	; r4 = intermediate value 1
	; r5 = intermediate value 2
	
	; save intermediate registers
	PUSH {r4, r5, r9, r10}
	
	; compare the value of DataPt and the address of DataBuffer and return if the Buffer is full
	LDR r9, [r2]
	CMP r0, r9
	BLT main

	; compare the value of TimePt and the address of TimeBuffer and return if the Buffer is full
	LDR r10, [r3]
	CMP r1, r10
	BLT main
	
	; get systick value and save in TimeBuffer
	LDR r4, =NVIC_ST_CURRENT_R
	LDR r4, [r4]
	STR r4, [r1]
	
	; read PE1 and PE0
	LDR r4, =SWITCH
	LDR r4, [r4]
	LDR r5, =LED
	LDR r5, [r5]
	
	; shift PE1 1 bit right, then 4 bits left
	LSR r4, r4, #1
	LSL r4, r4, #4
	
	; combine PE0 and PE1 into PE0-1
	ORR r5, r5, r4
	
	; store PE0-1 into DataBuffer
	STR r5, [r0]
	
	; increment DataBuffer address
	LDR r4, [r0], #4
	
	; increment TimeBuffer address
	LDR r4, [r1], #4
	
	; increment buffer pointer addresses
	ADD r9, r9, #4
	STR r9, [r2]
	ADD r10, r10, #4
	STR r10, [r3]
	
	; restore any registers saved and return
	PUSH {r4, r5, r9, r10}

	BX LR

;------------portEInit------------
; Init Port E and set PE0 as output, PE1 as input
portEInit
	; enable the clock for port E
	LDR r1, =SYSCTL_RCGCGPIO_R
	LDR r0, [r1]
	ORR r0, r0, #0x10
	STR r0, [r1]

	; allow time for the clock to activate
	NOP
	NOP

	; set PE0 as output (1), PE1 as input (0)
	LDR r1, =GPIO_PORTE_DIR_R
	MOV r0, #0x01
	STR r0, [r1]

	; enable PE0 and PE1
	LDR r1, =GPIO_PORTE_DEN_R
	MOV r0, #0x03
	STR r0, [r1]

	; set PE0 to ON
	LDR r1, =GPIO_PORTE_DATA_R
	MOV r0, #0x01
	STR r0, [r1]

	BX LR

;------------portFInit------------
; Init Port F and set PF0 as output
portFInit
	; enable the clock for port F
	LDR r1, =SYSCTL_RCGCGPIO_R
	LDR r0, [r1]
	ORR r0, r0, #0x20
	STR r0, [r1]

	; allow time for the clock to activate
	NOP
	NOP

	; set PF2 as an output (1)
	LDR r1, =GPIO_PORTF_DIR_R
	MOV r0, #0x04
	STR r0, [r1]

	; enable PF2
	LDR r1, =GPIO_PORTF_DEN_R
	MOV r0, #0x04
	STR r0, [r1]

	; set PF2 to ON
	LDR r1, =GPIO_PORTF_DATA_R
	MOV r0, #0x04
	STR r0, [r1]

	BX LR


	ALIGN      ; make sure the end of this section is aligned
	END        ; end of file
