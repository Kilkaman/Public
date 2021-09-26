#include "MDR1986VE8T.h"
#include "global_var_def.h"
  

void Clk_Init(void);
void PortInit(void);
void PortConf(void);
extern void TimerConfig(void);
extern void ADCInit(void);


Global_Var global_var;

int main()
{
unsigned int i1;
		
 		Global_Var* pgv;
			__disable_irq();
			Flag_Reg = 0;
			pgv = &global_var;
			PGV = pgv;
		
		for(i1 = 0; i1<sizeof(Global_Var); i1+=4)		
	*((unsigned int*)((int)pgv+i1)) = 0; // обнуляем глобальную структуру
	
	__enable_irq();
	Clk_Init();//настраеваем тактирование 64Mhz
  PortInit();//инициализируем порты
	ADCInit();//настраеваем АЦП
	TimerConfig(); //Настраеваем таймеры
	__enable_irq(); // разрешаем прерывания
	while(1);
}


void PortInit()
{

	PORTC->SANALOG = ((1<<2)|(1<<1)|(1<<0)|(0<<9));//PC0...2 - цифровые, PC9 - ADC3 (ADC0 CH1)
	PORTC->SPWR[0] = ((3<<4)|(3<<2)|(3<<0));       // PC0...2 - быстрый фронт 10 нс
	PORTC->SOE = ((1<<2)|(1<<1)|(1<<0));       // PC0...2 - вывод работает на выход

}


void Clk_Init()
{   
    clk->KEY = _KEY_;
    clk->PER0_CLK |= (1<<23)|(1<<24)|(1<<25)|(1<<26)|(1<<13)|(1<<14)|(1<<15)|(1<<17);//ТМR0.ТМR1,ТМR2,ТМR3,ТМR4, PORTA,PORTB,PORTC,PORTD,PORTE
	  clk->PER1_CLK |= (1<<24);         // ADC0 
	clk->HSE0_CLK = (1<<27);	                	
	while((clk->HSE0_STAT & (1<<20)) != (1<<20));	

}


void PortConf()// обновляем состояние порта
{
	Global_Var* pgv = PGV;
	if (pgv->C0) *(uint32_t*)PCRXTX |=1;
  else 	*(uint32_t*)PCRXTX &=~1;
	if (pgv->C1) *(uint32_t*)PCRXTX |=2;
  else 	*(uint32_t*)PCRXTX &=~2;
	if (pgv->C2) *(uint32_t*)PCRXTX |=4;
  else 	*(uint32_t*)PCRXTX &=~4;
}
