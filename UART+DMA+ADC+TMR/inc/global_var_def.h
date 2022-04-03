#define ADRRX 											0x20000000
#define ADRTX 											0x20000100
#define ADRMAX 										0x20001000
#define SIZE											0x3ff
#define CCR_CLEAR_Mask           	((uint32_t)0xFFFF800F)
#define MEMTOUART          				0xB2//(1<<1)|(1<<3)|(1<<4)|(1<<5)|(1<<7)
#define UARTTOMEM         				0xA2//(1<<1)|(1<<3)|(1<<5)|(1<<7)
#define ADCTOMEM         					0x5AA//(1<<1)|(1<<3)|(0<<4)|(1<<5)|(1<<7)|(1<<8)|(1<<10)//16бит - per,mem
//#define ADC_ON ADC1->CR2 |= ADC_CR2_ADON;  \
//                                ADC1->CR2 |= ADC_CR2_SWSTART; \
//                                DMA1_Channel1->CCR |= DMA_CCR1_TCIE | DMA_CCR1_EN;      //включаем преобразование прерывание DMA
//#define ADC_OFF ADC1->CR2 &= (~(ADC_CR2_ADON)); \
//                                DMA1_Channel1->CCR &= (~(DMA_CCR1_TCIE | DMA_CCR1_EN)); //выключаем преобразование и прерывание DMA

//структура глобальных переменных
typedef struct 
{
	uint8_t preamble;
	uint32_t cnt;
	uint8_t type;
	uint32_t length;
	//uint8_t data[255+1];
	
	uint32_t head;
	uint32_t tail;
	uint32_t rb;//неотправленные данные
	DMA_Channel_TypeDef* Channel;//активный канал
	uint8_t rx;
	
}
Pucket;
//глобальные переменные, располагаемые в регистрах R7-R12 для повышения производительности
//указатель на структуру глобальных переменных
register Pucket* PUC __asm("r11");
register unsigned int Flag_Reg __asm("r10");
