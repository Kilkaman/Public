#include "MDR32Fx.h"
#include "global_var_def.h"

void UART2Config(void);
void UART2_IRQHandler(void);

void TOout(unsigned int h, unsigned int t);
void bytesOUT(unsigned int h, unsigned int t);
void OutMass(void);

void UART2Config()
{
MDR_RST_CLK_TypeDef* rst_clk = MDR_RST_CLK;	
MDR_UART_TypeDef* uart2 = MDR_UART2;
	
	rst_clk->PER_CLOCK |= (1<<7);						//тактирование UART2
	rst_clk->UART_CLOCK |= (1<<25)|(2<<8);	//clock of UART2 = (16 MHz) HCLK/4
	uart2->IBRD = 2;	// speed of UART2 = 460800 bit/s	
  uart2->FBRD = 11;
//	uart2->IBRD = 8;	// speed of UART2 = 115200 bit/s	
//  uart2->FBRD = 44;
	uart2->LCR_H = (1<<4)|(3<<5);	// FIFO enable, 8-bits word
	uart2->CR = (1<<0)|(1<<8)|(1<<9);		// UART2, Tx, Rx enable 
	uart2->IFLS = (0<<0)|(1<<3);				//порог tx-1, rx-4(1/4)
	uart2->IMSC = 1<<4;									// Rx interrupt enable	
	NVIC->IP[UART2_IRQn] = (3<<5);			//приоритет UART2_IRQn 3
	NVIC->ISER[0] = (1<<UART2_IRQn);
}

void UART2_IRQHandler()
{

MDR_UART_TypeDef* uart = MDR_UART2;
Global_Var* pgv = PGV;
	
	if(uart->MIS & (1<<4))
	{
		
		
		int i1,i2;
		i1 = uart->DR & 0xff;
		i2 = (uart->DR & 0xff);
		i2 |= (uart->DR & 0xff) << 8;
		i2 |= (uart->DR & 0xff) << 16;
		switch(i1)
		{
			
				case (0x41):
				pgv->f_stream = 0;
				i2 = pgv->angle;	
				TOout(pgv->head, (pgv->head-4)&NSIZE);
//		   	uart->DR = i2 & 0xff;
//		  	uart->DR = (i2>>8) & 0xff;
//		  	uart->DR = (i2>>16) & 0xff;
//			  uart->DR = (i2>>24) & 0xff;
				break;
			
				case (0x42):
				pgv->f_stream = 1;
				TOout(pgv->head, (pgv->tail));
				break;

//				defoult:
//				uart->DR = 1;
//				uart->DR = 1;
//				uart->DR = 1;
//				uart->DR = 1;
//				break;
		}	
		
	}else 
		{
		
		OutMass();	
		
		
		}

}
void TOout(unsigned int h, unsigned int t )//t - всегда pgv->teil, h - всегда pgv->head
{
Global_Var* pgv = PGV;
MDR_UART_TypeDef* uart = MDR_UART2;
unsigned int ln;
pgv->tail = pgv->head;//устанавливаем метку для начала следующей отправки
pgv->t1 = t;// t1 - начало отправки 
ln = h - t ;

ln &= NSIZE;
pgv->n = ln;


uart->DR = ln & 0xff;
uart->DR = (ln >> 8) & 0xff;


if (ln<17)	bytesOUT(ln, t);
else 
	{
	bytesOUT(8, t);
		
	uart->IFLS |= 1; //буфер заполнен на 1/8
		uart->IMSC = (1 << 5);//разрешить только прерывания передатчика 
		// уходим в прерывание, в функцию OutMass();

	}
}


void OutMass(void)
{
Global_Var* pgv = PGV;
MDR_UART_TypeDef* uart = MDR_UART2;
 unsigned int ln;
 unsigned int lt;
	ln = pgv->n ;
 lt = pgv->t1;// промежуточное значение хвоста
if (ln > 9 ) 
		{
		bytesOUT(8, lt);
		}
else
	{
	if (!ln)
		{
	uart->IFLS = (0<<0)|(1<<3);				//порог tx-1, rx-4(1/4)
	uart->IMSC  = (1<<4);						// Уст. маску прерывания от таймаута приемника
		}
	else
		{
			bytesOUT(ln,lt);
		uart->IFLS = (0<<0)|(1<<3);				//порог tx-1, rx-4(1/4)
		
uart->IMSC  = (1<<4);						// Уст. маску прерывания от таймаута приемника


		}	
		
	}
}


void bytesOUT(unsigned int h, unsigned int t)
{
Global_Var* pgv = PGV;
MDR_UART_TypeDef* uart = MDR_UART2;
pgv->n -= h;// уменьшаем количество байт, которые надо отправить на количество отправляемых байт
while (h)
	{

	uart->DR = *(unsigned int*)(ADR0+t);

	t++; //увеличиваем значение хвоста
	t &= NSIZE;
		h--;
	}

	pgv->t1 = t;// записываем хвост в глобальную структуру

}

