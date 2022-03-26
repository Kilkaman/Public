#include "MDR32Fx.h"
#include "global_var_def.h"

extern void TimerConfig(void);
extern void UART2Config(void);
extern void SSP2Config(void);

Global_Var global_var;

int main()
{
Global_Var* pgv;	
unsigned int i1;
	
	__disable_irq();
	pgv = &global_var;
	PGV = pgv;
	for(i1 = 0; i1<sizeof(Global_Var); i1+=4)
		  *((unsigned int*)((int)pgv+i1)) = 0;	
pgv->angle = 5478;
	//for (i1= 0;i1<7936;i1++) pgv->buf_angle[i1] = 0x01020304&0xff;
	SSP2Config();
	TimerConfig();										// конфигурация таймерa
	UART2Config();										// конфигурация UART2
	
		
	__enable_irq();
	

	while(1)
	{
//		for(i1=0;i1<1000000;i1++);
//		MDR_PORTB->RXTX = 1<<1;
//		for(i1=0;i1<1000000;i1++);
//		MDR_PORTB->RXTX = 0;
	}
}

void Port_Init()
{
		MDR_RST_CLK->PER_CLOCK |= (1<<22)|(1<<23)|(1<<29)|(1<<24); //port B,C,F,D
// Инициализация порта B
		MDR_PORTB->ANALOG = (1<<1);		//светодиод
		MDR_PORTB->OE = (1<<1);	
		MDR_PORTB->PWR = (3<<2);
	
// Инициализация порта C
		MDR_PORTC->FUNC = (3<<2)|(3<<4);		//SSP2_CLK, SSP2_RXD
		MDR_PORTC->OE = (1<<1);			//SSP2_CLK
		MDR_PORTC->ANALOG = (1<<1)|(1<<2);	//FC, SSP2_CLK, SSP2_RXD
		MDR_PORTC->PWR = (3<<2);							//FC, SSP2_CLK
// Инициализация порта F
//		MDR_PORTF->FUNC = (3<<0)|(3<<2);		//UART2_RXD,UART2_TXD
//		MDR_PORTF->OE = (1<<1);			//UART2_TXD
//		MDR_PORTF->ANALOG = (1<<0)|(1<<1); 	//UART2_RXD,UART2_TXD 
//		MDR_PORTF->PULL = (1<<16);	//UART2_RXD
//		MDR_PORTF->PWR = (3<<2); 		//UART2_TXD
// Инициализация порта D
		MDR_PORTD->FUNC = (2<<0)|(2<<2);		//UART2_RXD,UART2_TXD
		MDR_PORTD->OE = (1<<1);			//UART2_TXD
		MDR_PORTD->ANALOG = (1<<0)|(1<<1); 	//UART2_RXD,UART2_TXD 
		MDR_PORTD->PULL = (1<<16);	//UART2_RXD
		MDR_PORTD->PWR = (3<<2); 		//UART2_TXD	
}

void Clk_Init()
{
unsigned int i1;	
MDR_RST_CLK_TypeDef* rst_clk = MDR_RST_CLK;
	
	rst_clk->HS_CONTROL = (1<<0);										//HSE - On; osc mode	 запуск внешнего осциллятора (2-16 МГц)
	while((rst_clk->CLOCK_STATUS & 0x04) != 0x04);	//Wait until HSE not ready	флаг выхода в рабочий режим осциллятора HSE
	rst_clk->CPU_CLOCK =  (2<<0)|(1<<8);						//HCLK = HSE (8 МГц)
	rst_clk->PLL_CONTROL = (1<<2)|(7<<8);						//блок умножения входной тактовой частоты, включаем PLL и умножаем частоту на 8
	while((rst_clk->CLOCK_STATUS & 0x02) != 0x02);	//Флаг выхода в рабочий режим CPU PLL
	rst_clk->PER_CLOCK |= (1<<3)|(1<<27);						//clock of BKP, EEPROM On 
	MDR_EEPROM->CMD = (2<<3);												//Задержка памяти программ при чтении в циклах								
	i1 = MDR_BKP->REG_0E;
	i1 |= 0x36;
	i1 &= ~((1<<6)|(1<<7));	
	MDR_BKP->REG_0E = i1;														//подгрузка LDO, запрет JTAG 
	rst_clk->CPU_CLOCK = (2<<0)|(1<<2)|(1<<8);			//CPU Clock = HSE (64MHz)		
	rst_clk->PER_CLOCK &= ~((1<<3)|(1<<27));				// clock of BKP, EEPROM Off
}
	
void Sys_Init()
{
	Port_Init();
	Clk_Init();
}
