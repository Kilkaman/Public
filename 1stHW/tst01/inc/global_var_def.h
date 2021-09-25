#define ADR0 											0x20000000
#define ADRMAX 										0x20000000
#define CCR_CLEAR_Mask           	((uint32_t)0xFFFF800F)
#define MEMTOUART          				0xB2//(1<<1)|(1<<3)|(1<<4)|(1<<5)|(1<<7)
#define UARTTOMEM         				0xA2//(1<<1)|(1<<3)|(1<<5)|(1<<7)

//структура глобальных переменных
typedef struct 
{
	uint8_t preamble;
	uint8_t cnt;
	uint8_t type;
	uint8_t length;
	//uint8_t data[255+1];
	volatile uint8_t* Adr0;// я решил выделить некоторую область памяти для данных, вместо массива 
	uint8_t head;
	uint8_t tail;
	
}
Pucket;
//глобальные переменные, располагаемые в регистрах R7-R12 для повышения производительности
//указатель на структуру глобальных переменных
register Pucket* PUC __asm("r11");
register unsigned int Flag_Reg __asm("r10");
