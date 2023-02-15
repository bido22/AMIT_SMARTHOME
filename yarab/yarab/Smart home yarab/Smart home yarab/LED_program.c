/*
 * LED_program.c
 *
 * Created: 9/25/2022 5:15:59 PM
 *  Author: Mazen
 */ 
/* utils */
#include "STD_types.h"
#include "bitmath.h"
#include "ATMEGA32_REG.h"

/* mcal */
#include "DIO_INTERFACE.h" 
//hal
#include "LED_interface.h"


void LED_ON(u8 portId,u8 pinId,u8 connectionType)
{
	if(portId > 3 || pinId > 7 || (connectionType != LED_forward && connectionType != LED_reverse))
		return;
	
	DIO_setPinDirection(portId,pinId,DIO_PIN_OUTPUT);
	DIO_setPinValue(portId,pinId,!connectionType);	
}

void LED_OFF(u8 portId,u8 pinId,u8 connectionType)
{
	if(portId > 3 || pinId > 7 || (connectionType != LED_forward && connectionType != LED_reverse))
		return;
	
	DIO_setPinDirection(portId,pinId,DIO_PIN_OUTPUT);
	DIO_setPinValue(portId,pinId,connectionType);
}

void LED_Toggle(u8 portId,u8 pinId){
	DIO_togglePin(portId,pinId);
}