
Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

				PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
	            EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemoryMngFault_Handler    ; MemoryMngFault_Handler
                DCD     BusFault_Handler          ; BusFault_Handler
                DCD     UsageFault_Handler        ; UsageFault_Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVCall_Handler            ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     Systick_Handler           ; SysTick Handler
                DCD     0           			  ; Reserved16
                DCD     0          				  ; Reserved17
                DCD     0           			  ; Reserved18
                DCD     0           			  ; Reserved19
                DCD     0           			  ; Reserved20
                DCD     0           			  ; Reserved21
                DCD     0           			  ; Reserved22
                DCD     0           			  ; Reserved23
                DCD     0           			  ; Reserved24
                DCD     0           			  ; Reserved25
                DCD     0           			  ; Reserved26
                DCD     0           			  ; Reserved27
                DCD     0           			  ; Reserved28
                DCD     0           			  ; Reserved29
                DCD     0           			  ; Reserved30
                DCD     0          				  ; Reserved31
                DCD     0           			  ; Reserved32
                DCD     0           			  ; Reserved33
                DCD     0           			  ; Reserved34
                DCD     0           			  ; Reserved35
                DCD     0           			  ; Reserved36
                DCD     0           			  ; Reserved37
				DCD 	0	
				DCD 	0	
				DCD 	0	
				DCD 	0	
				DCD 	0	
				DCD 	0	
				DCD 	0	
				DCD 	0	
				DCD 	0	
				DCD 	0	
                DCD     FT_IF0_Handler            ; FT_IF0_Handler
                DCD     FT_IF1_Handler            ; FT_IF1_Handler
                DCD     FT_IF2_Handler            ; FT_IF2_Handler
                DCD     FT_IF3_Handler            ; FT_IF3_Handler
                DCD     CLK_IF_Handler            ; CLK_IF_Handler
                DCD     PVD_IF_Handler            ; PVD_IF_Handler
                DCD     RTC_IF_Handler            ; RTC_IF_Handler
                DCD     BKP_IF_Handler            ; BKP_IF_Handler
                DCD     EXT_INTERROR0_Handler     ; EXT_INTERROR0_Handler
                DCD     EXT_INTERROR1_Handler     ; EXT_INTERROR1_Handler
                DCD     EXT_INTERROR2_Handler     ; EXT_INTERROR2_Handler
                DCD     EXT_INTERROR3_Handler     ; EXT_INTERROR3_Handler
                DCD     EXT_INTERROR4_Handler     ; EXT_INTERROR4_Handler
                DCD     EXT_INTERROR5_Handler     ; EXT_INTERROR5_Handler
                DCD     EXT_INTERROR6_Handler     ; EXT_INTERROR6_Handler
                DCD     EXT_INTERROR7_Handler     ; EXT_INTERROR7_Handler
                DCD     IF_ERR_SCR_Handler        ; IF_ERR_SCR_Handler					
                DCD     IF_FIN_SCR_Handler        ; IF_FIN_SCR_Handler					
                DCD     DMA_ERR_Handler           ; DMA_ERR_Handler	
                DCD     DMA_DONE0_Handler         ; DMA_DONE0_Handler	
                DCD     DMA_DONE1_Handler         ; DMA_DONE1_Handler
                DCD     DMA_DONE2_Handler		  ; DMA_DONE2_Handler	
                DCD     DMA_DONE3_Handler 		  ; DMA_DONE3_Handler	
                DCD     0         				  ; DMA_DONE4_Handler	
                DCD     0         				  ; DMA_DONE5_Handler	
                DCD     0         				  ; DMA_DONE6_Handler	
                DCD     0         				  ; DMA_DONE7_Handler	
                DCD     0         				  ; DMA_DONE8_Handler	
                DCD     0         				  ; DMA_DONE9_Handler	
                DCD     0        				  ; DMA_DONE10_Handler	
                DCD     0        				  ; DMA_DONE11_Handler
                DCD     0        				  ; DMA_DONE12_Handler	
                DCD     0        				  ; DMA_DONE13_Handler
                DCD     0        				  ; DMA_DONE14_Handler	
                DCD     0        				  ; DMA_DONE15_Handler	
                DCD     0        				  ; DMA_DONE16_Handler	
                DCD     0        				  ; DMA_DONE17_Handler	
                DCD     0        				  ; DMA_DONE18_Handler	
                DCD     0        				  ; DMA_DONE19_Handler	
                DCD     0        				  ; DMA_DONE20_Handler	
                DCD     0        				  ; DMA_DONE21_Handler	
                DCD     0        				  ; DMA_DONE22_Handler	
                DCD     0        				  ; DMA_DONE23_Handler
                DCD     0        				  ; DMA_DONE24_Handler	
                DCD     0        				  ; DMA_DONE25_Handler
                DCD     0        				  ; DMA_DONE26_Handler	
                DCD     0        				  ; DMA_DONE27_Handler	
                DCD     0        				  ; DMA_DONE28_Handler	
                DCD     0        				  ; DMA_DONE29_Handler	
                DCD     0        				  ; DMA_DONE30_Handler	
                DCD     0        				  ; DMA_DONE31_Handler				
                DCD     IRQ_PORTA_Handler         ; IRQ_PORTA_Handler					
                DCD     IRQ_PORTB_Handler         ; IRQ_PORTB_Handler
                DCD     IRQ_PORTC_Handler         ; IRQ_PORTC_Handler
                DCD     IRQ_PORTD_Handler         ; IRQ_PORTD_Handler
                DCD     IRQ_PORTE_Handler         ; IRQ_PORTE_Handler
                DCD     IRQ_PORTF_Handler         ; IRQ_PORTF_Handler
                DCD     INT_ETH0_Handler          ; INT_ETH0_Handler
                DCD     INT_ETH1_Handler          ; INT_ETH1_Handler	
				DCD     INT_SPW0_Handler          ; INT_SPW0_Handler
                DCD     INT_SPW1_Handler          ; INT_SPW1_Handler
                DCD     INT_TMR0_Handler          ; INT_TMR0_Handler
                DCD     INT_TMR1_Handler          ; INT_TMR1_Handler
                DCD     INT_TMR2_Handler          ; INT_TMR2_Handler
                DCD     INT_TMR3_Handler          ; INT_TMR3_Handler
                DCD     INT_TMR4_Handler          ; INT_TMR4_Handler
                DCD     INT_TMR5_Handler          ; INT_TMR5_Handler
                DCD     INT_CAN0_Handler          ; INT_CAN0_Handler
                DCD     INT_CAN1_Handler          ; INT_CAN1_Handler
                DCD     INT_CAN2_Handler          ; INT_CAN2_Handler
                DCD     INT_CAN3_Handler          ; INT_CAN3_Handler
                DCD     INT_CAN4_Handler          ; INT_CAN4_Handler				
                DCD     INT_SSP0_Handler          ; INT_SSP0_Handler	
                DCD     INT_SSP1_Handler          ; INT_SSP1_Handler
                DCD     INT_SSP2_Handler          ; INT_SSP2_Handler
                DCD     INT_SSP3_Handler          ; INT_SSP3_Handler
                DCD     INT_UART0_Handler         ; INT_UART0_Handler
                DCD     INT_UART1_Handler         ; INT_UART1_Handler
                DCD     INT_UART2_Handler         ; INT_UART2_Handler
                DCD     INT_UART3_Handler         ; INT_UART3_Handler
                DCD     INT_USB_Handler           ; INT_USB_Handler
                DCD     INT_RX_ARC0_Handler       ; INT_RX_ARC0_Handler
                DCD     INT_TX_ARC0_Handler       ; INT_TX_ARC0_Handler
                DCD     INT_RX_ARC1_Handler       ; INT_RX_ARC1_Handler
                DCD     INT_TX_ARC1_Handler       ; INT_TX_ARC1_Handler
                DCD     INT_MIL0_Handler          ; INT_MIL0_Handler
                DCD     INT_MIL1_Handler          ; INT_MIL1_Handler
                DCD     INT_ADC0_Handler          ; INT_ADC0_Handler
                DCD     INT_ADC1_Handler          ; INT_ADC1_Handler
                DCD     INT_DAC0_Handler          ; INT_DAC0_Handler
                DCD     INT_DAC1_Handler          ; INT_DAC1_Handler					
                DCD     INT_CRYPTO_Handler        ; INT_CRYPTO_Handler	
                DCD     INT_CRC_Handler           ; INT_CRC_Handler					
                DCD     INT_ECC_Handler           ; INT_ECC_Handler								
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors
	
                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler			[WEAK]
				IMPORT  __main
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)                

NMI_Handler     PROC
                EXPORT  NMI_Handler					[WEAK]
                B       .
                ENDP

HardFault_Handler     PROC
                EXPORT  HardFault_Handler			[WEAK]
                B       .
                ENDP

MemoryMngFault_Handler     PROC
                EXPORT  MemoryMngFault_Handler		[WEAK]
                B       .
                ENDP

BusFault_Handler     PROC
                EXPORT  BusFault_Handler			[WEAK]
                B       .
                ENDP

UsageFault_Handler     PROC
                EXPORT  UsageFault_Handler			[WEAK]
                B       .
                ENDP

SVCall_Handler     PROC
                EXPORT  SVCall_Handler				[WEAK]
                B       .
                ENDP

PendSV_Handler     PROC
                EXPORT  PendSV_Handler				[WEAK]
                B       .
                ENDP

Systick_Handler     PROC
                EXPORT  Systick_Handler				[WEAK]
                B       .
                ENDP
                
Default_Handler PROC
	
				EXPORT  FT_IF0_Handler				[WEAK]
				EXPORT  FT_IF1_Handler				[WEAK]
				EXPORT  FT_IF2_Handler				[WEAK]
				EXPORT  FT_IF3_Handler				[WEAK]
                EXPORT  CLK_IF_Handler				[WEAK]
                EXPORT  PVD_IF_Handler				[WEAK]
                EXPORT  RTC_IF_Handler				[WEAK]
                EXPORT  BKP_IF_Handler				[WEAK]					
                EXPORT  EXT_INTERROR0_Handler		[WEAK]
                EXPORT  EXT_INTERROR1_Handler		[WEAK]					
				EXPORT  EXT_INTERROR2_Handler		[WEAK]
                EXPORT  EXT_INTERROR3_Handler		[WEAK]
                EXPORT  EXT_INTERROR4_Handler		[WEAK]					
                EXPORT  EXT_INTERROR5_Handler		[WEAK]
				EXPORT  EXT_INTERROR6_Handler		[WEAK]
				EXPORT  EXT_INTERROR7_Handler		[WEAK]
                EXPORT  IF_ERR_SCR_Handler			[WEAK]
                EXPORT  IF_FIN_SCR_Handler			[WEAK]
                EXPORT  DMA_ERR_Handler				[WEAK]
                EXPORT  DMA_DONE0_Handler			[WEAK]
                EXPORT  DMA_DONE1_Handler			[WEAK]
                EXPORT  DMA_DONE2_Handler			[WEAK]
                EXPORT  DMA_DONE3_Handler			[WEAK]
                EXPORT  IRQ_PORTA_Handler			[WEAK]
                EXPORT  IRQ_PORTB_Handler			[WEAK]
                EXPORT  IRQ_PORTC_Handler			[WEAK]
 				EXPORT  IRQ_PORTD_Handler			[WEAK]
                EXPORT  IRQ_PORTE_Handler			[WEAK]
                EXPORT  IRQ_PORTF_Handler			[WEAK]
                EXPORT  INT_ETH0_Handler			[WEAK]
                EXPORT  INT_ETH1_Handler			[WEAK]
                EXPORT  INT_SPW0_Handler			[WEAK]
                EXPORT  INT_SPW1_Handler			[WEAK]
                EXPORT  INT_TMR0_Handler			[WEAK]
                EXPORT  INT_TMR1_Handler			[WEAK]
                EXPORT  INT_TMR2_Handler			[WEAK]
                EXPORT  INT_TMR3_Handler			[WEAK]
                EXPORT  INT_TMR4_Handler			[WEAK]
                EXPORT  INT_TMR5_Handler			[WEAK]
                EXPORT  INT_CAN0_Handler			[WEAK]
                EXPORT  INT_CAN1_Handler			[WEAK]
				EXPORT  INT_CAN2_Handler			[WEAK]
                EXPORT  INT_CAN3_Handler			[WEAK]
                EXPORT  INT_CAN4_Handler			[WEAK]
                EXPORT  INT_SSP0_Handler			[WEAK]
                EXPORT  INT_SSP1_Handler			[WEAK]	
                EXPORT  INT_SSP2_Handler			[WEAK]
                EXPORT  INT_SSP3_Handler			[WEAK]
                EXPORT  INT_UART0_Handler			[WEAK]
                EXPORT  INT_UART1_Handler			[WEAK]
                EXPORT  INT_UART2_Handler			[WEAK]
                EXPORT  INT_UART3_Handler			[WEAK]
                EXPORT  INT_USB_Handler				[WEAK]
                EXPORT  INT_RX_ARC0_Handler			[WEAK]
                EXPORT  INT_TX_ARC0_Handler			[WEAK]
                EXPORT  INT_RX_ARC1_Handler			[WEAK]
                EXPORT  INT_TX_ARC1_Handler			[WEAK]
                EXPORT  INT_MIL0_Handler			[WEAK]
                EXPORT  INT_MIL1_Handler			[WEAK]
                EXPORT  INT_ADC0_Handler			[WEAK]
                EXPORT  INT_ADC1_Handler			[WEAK]
                EXPORT  INT_DAC0_Handler			[WEAK]
                EXPORT  INT_DAC1_Handler			[WEAK]
                EXPORT  INT_CRYPTO_Handler			[WEAK]
                EXPORT  INT_CRC_Handler				[WEAK]
                EXPORT  INT_ECC_Handler				[WEAK]					
					
FT_IF0_Handler
FT_IF1_Handler
FT_IF2_Handler
FT_IF3_Handler
CLK_IF_Handler
PVD_IF_Handler 
RTC_IF_Handler
BKP_IF_Handler
EXT_INTERROR0_Handler 
EXT_INTERROR1_Handler
EXT_INTERROR2_Handler
EXT_INTERROR3_Handler
EXT_INTERROR4_Handler
EXT_INTERROR5_Handler
EXT_INTERROR6_Handler
EXT_INTERROR7_Handler
IF_ERR_SCR_Handler
IF_FIN_SCR_Handler
DMA_ERR_Handler
DMA_DONE0_Handler					
DMA_DONE1_Handler
DMA_DONE2_Handler
DMA_DONE3_Handler
IRQ_PORTA_Handler
IRQ_PORTB_Handler
IRQ_PORTC_Handler
IRQ_PORTD_Handler
IRQ_PORTE_Handler					
IRQ_PORTF_Handler					
INT_ETH0_Handler					
INT_ETH1_Handler					
INT_SPW0_Handler					
INT_SPW1_Handler					
INT_TMR0_Handler					
INT_TMR1_Handler					
INT_TMR2_Handler					
INT_TMR3_Handler					
INT_TMR4_Handler					
INT_TMR5_Handler
INT_CAN0_Handler					
INT_CAN1_Handler					
INT_CAN2_Handler					
INT_CAN3_Handler					
INT_CAN4_Handler					
INT_SSP0_Handler					
INT_SSP1_Handler
INT_SSP2_Handler
INT_SSP3_Handler					
INT_UART0_Handler
INT_UART1_Handler
INT_UART2_Handler
INT_UART3_Handler					
INT_USB_Handler					
INT_RX_ARC0_Handler					
INT_TX_ARC0_Handler					
INT_RX_ARC1_Handler					
INT_TX_ARC1_Handler					
INT_MIL0_Handler					
INT_MIL1_Handler					
INT_ADC0_Handler					
INT_ADC1_Handler
INT_DAC0_Handler
INT_DAC1_Handler
INT_CRYPTO_Handler
INT_CRC_Handler
INT_ECC_Handler
                B       .
				NOP
                ENDP
                
                EXPORT  __initial_sp
					
;				AREA    RAM_VECT, DATA, READWRITE, ALIGN=10
;Ram_Vectors     SPACE   __Vectors_Size
;				EXPORT  Ram_Vectors

              END
