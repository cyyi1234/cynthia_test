#include "uart.h"

unsigned char *pchar;                      

// timer0 internel time=11.0592Mhz
void delay_1ms(unsigned int ms) {
    unsigned int i;
    
    // init timer0
    TMOD &= 0xF0;      // clear timer0 mode
    TMOD |= 0x01;      // set timer0 to 16-bit timer mode
    
    for (i = 0; i < ms; i++) {
        TH0 = 0xFC;    // high bit for init value
        TL0 = 0x18;    // low bit for init value
        
        TR0 = 1;       // start timer0
        while (TF0 == 0); // waiting for overflow
        TF0 = 0;       // Clear overflow flags
        TR0 = 0;       // stop timer0
    }
}

#if 0
void delay_100us(unsigned int us) {
    unsigned int i;
    
    TMOD &= 0xF0;      
    TMOD |= 0x01; 
    for (i = 0; i < us; i++)
	  {
      TH0 = 0xFF;    
      TL0 = 0x9C;   
        
      TR0 = 1;       
      while (TF0 == 0); 
      TF0 = 0;       
      TR0 = 0;  
    }
	}
#endif
	
void Uart_Init(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8bit and variable baudrate, mode 1
	T2L = (65536 - (FOSC/4/BAUD));			//Initial timer value
	T2H = (65536 - (FOSC/4/BAUD))>>8;		//Set reload value
	AUXR = 0x14;		//Timer2 running 1 machine cycle is 1 clock cycle, start T2
	AUXR |= 0x01;   //T2 for UART1
	ES=1; 		//uart1 enable interrupt
	REN=1;    //uart can receive data
	
	TI=1;
	
}

void Uart_SendByte(unsigned char sbyte)
{  
     SBUF=sbyte; 	//write data into SBUF register				
     while(!TI); 					
     TI=0; 						//clear sent flag	
}

//mapping printf
char putchar(char c)
{
	Uart_SendByte((unsigned char)c);
	return c;
}

#if 0
void Uart_SendString(unsigned char *pstr)
{
     while(*pstr!='\0') 			
     {
         Uart_SendByte(*pstr);			
         pstr++; 					
     } 
}

void Uart() interrupt 4 
{ 
	//rev interrupt flag
  if(RI)
	{
		RI = 0; //clear RI
		//*pchar = SBUF;
		//Uart_SendByte(*pchar); //send the rev_data
		Uart_SendByte(SBUF); //send the rev_data
	}
  //send interrupt flag
  if(TI)
	{
		TI = 0;  //clear TI bit
	}		
}
#endif