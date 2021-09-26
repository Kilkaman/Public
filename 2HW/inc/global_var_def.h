#include "MDR1986VE8T.h"
//структура глобальных переменных
#define TIMER0  MDR_TMR0
#define TIMER1  MDR_TMR1
#define TIMER2  MDR_TMR2
#define TIMER3  MDR_TMR3
#define clk     CLK_CNTR
#define _KEY_ 0x8555AAA1
#define PCRXTX  0x40082004 



typedef struct 
{
 uint8_t ADCN;
 uint16_t ADC_mean_val;
	int ADC_sum_val;
  uint8_t* C0;
	uint8_t* C1;
  uint8_t* C2;
}Global_Var;

//глобальные переменные, располагаемые в регистрах R7-R12 для повышения производительности
//указатель на структуру глобальных переменных
register Global_Var* PGV __asm("r11");
register unsigned int Flag_Reg __asm("r10");






