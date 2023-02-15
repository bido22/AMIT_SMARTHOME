/*
 * AdminPrevilages.c
 *
 * Created: 15-Feb-23 10:49:46 AM
 *  Author: Marwan Yasser
 */ 

#include "Admin_Interface.h"
#include "../../UART_interface.h"

void Admin_sendString(u8* adminString){
	UART_sendString(adminString);
	UART_sendString("\r\n");
}

void Admin_newLine(){
} 

void Admin_recieveInput(u8* adminInput){
	UART_receive(adminInput);
}

void Admin_wrongInput(){
	
}

void Admin_clearDisplay(){
	
}

