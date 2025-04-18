#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define usart_bound   9600   /**  串口波特率  **/
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节
extern u16 USART_RX_STA;         		//接收状态标记	
void uart_init(u32 bound);
void uart2_init(u32 bound);

#endif




