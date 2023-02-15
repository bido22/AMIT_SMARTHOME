/*
 * Guest_program.c
 *
 * Created: 15-Feb-23 10:52:33 AM
 *  Author: Marwan Yasser
 */ 

#include "Guest_Interface.h"
#include "../../KPD_interface.h"
#include "../../LCD_interface.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void Guest_sendString(u8* guestString){
	LCD_writeString(guestString);
}

void Guest_newLine(){
	LCD_goTo(1,0);
}

void Guest_recieveInput(u8* guestInput){
	*guestInput=KPD_NOT_PRESSED;
	do 
	{
		KPD_getvalue(guestInput);
	} while (*guestInput == KPD_NOT_PRESSED);
}

void Guest_wrongInput(){
	LCD_clear();
	LCD_writeString("Wrong input");
	_delay_ms(500);
	LCD_clear();
	_delay_ms(100);
}

void Guest_clearDisplay(){
	LCD_clear();
}
