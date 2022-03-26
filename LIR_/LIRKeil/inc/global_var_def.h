#include "MDR32Fx.h"

//структура глобальных переменных
typedef struct 
{
unsigned char nmbtx;	
unsigned short it;
unsigned int angle;
unsigned short ibuf_rxlir;	
unsigned short ibuf_txuart;
//unsigned int buf_angle[7936];	
//unsigned int buf_angle[4096];	
char f_stream;
unsigned int	head, tail, t1, t2, t3, n, h1;	
#define ADR0 0x20000000
	#define NSIZE 0x1FFF 
	
}Global_Var;

//глобальные переменные, располагаемые в регистрах R7-R12 для повышения производительности
//указатель на структуру глобальных переменных
register Global_Var* PGV __asm("r11");

