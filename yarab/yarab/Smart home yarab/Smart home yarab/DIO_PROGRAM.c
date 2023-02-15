/*
 * DIO_PROGRAM.c
 *
 * Created: 9/4/2022 9:38:27 PM
 *  Author: Mazen
 */ 

/* utils */
#include "STD_types.h"
#include "bitmath.h"
#include "ATMEGA32_REG.h"

/* mcal */
#include "DIO_INTERFACE.h" 

void DIO_setPinDirection(u8 PortId,u8 PinId,u8 PinDirection)
{
	
	if( (PortId<=3) &&  (PinId<=7) && (PinDirection==DIO_PIN_OUTPUT || PinDirection==DIO_PIN_INPUT ) )
	{
		switch(PortId)
		{
			case DIO_PORTA:
			if(PinDirection==DIO_PIN_OUTPUT)
			SET_BIT(DDRA,PinId);
			else
			CLR_BIT(DDRA,PinId);
			break;
			
			case DIO_PORTB:
			if(PinDirection==DIO_PIN_OUTPUT)
			SET_BIT(DDRB,PinId);
			else
			CLR_BIT(DDRB,PinId);
			break;
			
			case DIO_PORTC:
			if(PinDirection==DIO_PIN_OUTPUT)
			SET_BIT(DDRC,PinId);
			else
			CLR_BIT(DDRC,PinId);
			break;
			
			case DIO_PORTD:
			if(PinDirection==DIO_PIN_OUTPUT)
			SET_BIT(DDRD,PinId);
			else
			CLR_BIT(DDRD,PinId);
			break;
		}
	}
	
}
void DIO_setPinValue(u8 PortId,u8 PinId,u8 PinValue)
{
	if( (PortId<=3) &&  (PinId<=7) && (PinValue==DIO_PIN_HIGH || PinValue==DIO_PIN_LOW ) )
	{
		switch(PortId)
		{
			case DIO_PORTA:
			if(PinValue==DIO_PIN_HIGH)
			SET_BIT(PORTA,PinId); 
			else
			CLR_BIT(PORTA,PinId);
			break;
			
			case DIO_PORTB:
			if(PinValue==DIO_PIN_HIGH)
			SET_BIT(PORTB,PinId);
			else
			CLR_BIT(PORTB,PinId);
			break;
			
			case DIO_PORTC:
			if(PinValue==DIO_PIN_HIGH)
			SET_BIT(PORTC,PinId);
			else
			CLR_BIT(PORTC,PinId);
			break;
			
			case DIO_PORTD:
			if(PinValue==DIO_PIN_HIGH)
			SET_BIT(PORTD,PinId);
			else
			CLR_BIT(PORTD,PinId);
			break;
		}
	}
}
void DIO_getPinValue(u8 PortId,u8 PinId,u8* PinValue)
{
	if((PortId<=3) && (PinId<=7) && (PinValue != NULL))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			if( DIO_PIN_HIGH==GET_BIT(PINA,PinId))
			{
				*PinValue=DIO_PIN_HIGH;
			}
			else
			{
				*PinValue=DIO_PIN_LOW;
			}
			break;
			
			
			case DIO_PORTB:
			if(GET_BIT(PINB,PinId)==DIO_PIN_HIGH)
			{
				*PinValue=DIO_PIN_HIGH;
			}
			else
			{
				*PinValue=DIO_PIN_LOW;
			}
			break;
			
			case DIO_PORTC:
			if(DIO_PIN_HIGH==GET_BIT(PINC,PinId))
			{
				*PinValue=DIO_PIN_HIGH;
			}
			else
			{
				*PinValue=DIO_PIN_LOW;
			}
			break;
			
			case DIO_PORTD:
			if(DIO_PIN_HIGH==GET_BIT(PIND,PinId))
			{
				*PinValue=DIO_PIN_HIGH;
			}
			else
			{
				*PinValue=DIO_PIN_LOW;
			}
			break;
		}
	}
}
void DIO_togglePin(u8 PortId,u8 PinId)
{
	if( (PortId<=3) && (PinId<=7) )
	{
		switch(PortId)
		{
			case DIO_PORTA:
			TGL_BIT(PORTA,PinId);
			break;
			
			case DIO_PORTB:
			TGL_BIT(PORTB,PinId);
			break;
			
			case DIO_PORTC:
			TGL_BIT(PORTC,PinId);
			break;
			
			case DIO_PORTD:
			TGL_BIT(PORTD,PinId);
			break;
		}
	}
	
}
void DIO_setInputPinResistance(u8 PortId,u8 PinId)
{
	if( (PortId<=3) && (PinId<=7) )
	{
		switch(PortId)
		{
			case DIO_PORTA:
			SET_BIT(PORTA,PinId);
			break;
			
			case DIO_PORTB:
			SET_BIT(PORTB,PinId);
			break;
			
			case DIO_PORTC:
			SET_BIT(PORTC,PinId);
			break;
			
			case DIO_PORTD:
			SET_BIT(PORTD,PinId);
			break;
		}
	}
}



void DIO_setPortDirection(u8 PortId,u8 PortDirection)
{
	if((PortId<=3) && (PortDirection==DIO_PORT_INPUT || PortDirection==DIO_PORT_OUTPUT))
	{
		switch(PortId)
		{
			case DIO_PORTA:
			if(PortDirection==DIO_PORT_OUTPUT)
			DDRA=0xff;
			else
			DDRA=0x00;
			break;
			
			case DIO_PORTB:
			if(PortDirection==DIO_PORT_OUTPUT)
			DDRB=0xff;
			else
			DDRB=0x00;
			break;
			
			case DIO_PORTC:
			if(PortDirection==DIO_PORT_OUTPUT)
			DDRC=0xff;
			else
			DDRC=0x00;
			break;
			
			case DIO_PORTD:
			if(PortDirection==DIO_PORT_OUTPUT)
			DDRD=0xff;
			else
			DDRD=0x00;
			break;
		}
	}
	
}
void DIO_setPortValue(u8 PortId,u8 PortValue)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case DIO_PORTA:
			PORTA=PortValue;
			break;
			
			case DIO_PORTB:
			PORTB=PortValue;
			break;
			
			case DIO_PORTC:
			PORTC=PortValue;
			break;
			
			case DIO_PORTD:
			PORTD=PortValue;
			break;
		}
	}
}
void DIO_getPortValue(u8 PortId,u8* PortValue)
{
	if(PortId<=3 && PortValue!=NULL)
	{
		switch(PortId)
		{
			case DIO_PORTA:
			*PortValue=PINA;
			break;
			
			case DIO_PORTB:
			*PortValue=PINB;
			break;
			
			case DIO_PORTC:
			*PortValue=PINC;
			break;
			
			case DIO_PORTD:
			*PortValue=PIND;
			break;
		}
	}
	
}
void DIO_togglePort(u8 PortId)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case DIO_PORTA:
			PORTA=~PORTA;
			break;
			
			case DIO_PORTB:
			PORTB=~PORTB;
			break;
			
			case DIO_PORTC:
			PORTC=~PORTC;
			break;
			
			case DIO_PORTD:
			PORTD=~PORTD;
			break;
		}
	}
}
void DIO_setInputPortResistance(u8 PortId)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
			case DIO_PORTA:
			PORTA=0xff;
			break;
			
			case DIO_PORTB:
			PORTB=0xff;
			break;
			
			case DIO_PORTC:
			PORTC=0xff;
			break;
			
			case DIO_PORTD:
			PORTD=0xff;
			break;
		}
	}
}