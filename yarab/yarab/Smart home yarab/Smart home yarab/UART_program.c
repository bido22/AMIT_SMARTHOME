/*
 * UART_program.c
 *
 * Created: 10/15/2022 2:41:50 AM
 *  Author: meow
 */ 
//utils
#include "ATMEGA32_REG.h"
#include "STD_Types.h"
#include "bitmath.h"
//mcal
#include "UART_interface.h"


void UART_init(void)
{
	// writing ucsrc, select uart mode asynchronous, configure no parity, configure data bits = 8 , configure stop bits = 1
	UCSRC=0x86; //0b10000110
	// select data size
	CLR_BIT(UCSRB,2);
	// configure baud rate = 9600
	UBRRL=103;	
	// enable transmitter and receiver
	SET_BIT(UCSRB,4);
	SET_BIT(UCSRB,3);
}
void UART_sendString(u8* string)
{
	if(string != NULL)
	{
		while(*string) 
		{
			UART_send(*string);
			string++;
		}
	}
	else
	{
		// do nothing 
	}
	
}
void UART_send(u8 data)
{
	UDR=data;
	while(GET_BIT(UCSRA,5)==0);
}
void UART_receive(u8* returnedData)
{
	if(returnedData!=NULL)
	{
		while(GET_BIT(UCSRA,7)==0);
		*returnedData=UDR;
	}
}