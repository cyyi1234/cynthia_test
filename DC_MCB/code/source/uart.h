#ifndef __UART_H_
#define __UART_H_
#include <stc15.h>
#include <stdio.h>
#include <intrins.h>
extern unsigned char *pchar;
#define FOSC 11059200L          //ICR freq
#define BAUD 9600               //baudrate

extern void delay_1ms(unsigned int ms); 

void delay_1ms(unsigned int ms); 
void delay_100us(unsigned int us);
void Uart_Init(void);	
unsigned char Uart_ReceiveByte(void);			
void Uart_SendString(unsigned char *pstr);	

#endif