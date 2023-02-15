/*
 * LCD_program.c
 *
 * Created: 9/10/2022 10:21:50 AM
 *  Author: Kimo Store
 */ 

#define  F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */

#include "bitmath.h"
#include "STD_types.h"
#include "ATMEGA32_REG.h"

/*  MCAL */
#include "DIO_INTERFACE.h"

/*HAL*/
#include "LCD_interface.h"
#include "LCD_config.h"


void writeHalfPort(u8 value) /* we like to name the argument value not register although they are the same because we pass the register in the form of 8 bits 
									 * not in the form of words like we did before with words like  PORTA and PINA etc */
{    
										
			    /* this function takes (((( the first 4 bits(LSB) )))) of the register passed to it 
	             * and then copies them in DIO_PORTA in pin 4,5,6 and 7 (or any place but this was amit's kit connection)
				 * (on the PORT register)-->(the DIO_SetPinValue deals with the PORT register) */
	
	if (GET_BIT(value,0)==1){
	
	
	DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_HIGH);
	
	
	}
	else{
		
	DIO_setPinValue(DIO_PORTA,DIO_PIN4,DIO_PIN_LOW);
		
	}
	if (GET_BIT(value,1)==1){
		
		
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_HIGH);
		
		
	}
	else{
		
		DIO_setPinValue(DIO_PORTA,DIO_PIN5,DIO_PIN_LOW);
		
	}
	if (GET_BIT(value,2)==1){
		
		
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_HIGH);
		
		
	}
	else{
		
		DIO_setPinValue(DIO_PORTA,DIO_PIN6,DIO_PIN_LOW);
		
	}
	if (GET_BIT(value,3)==1){
		
		
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_HIGH);
		
		
	}
	else{
		
		DIO_setPinValue(DIO_PORTA,DIO_PIN7,DIO_PIN_LOW);
		
	}
		
	
}


void LCD_sendCmnd(u8 cmnd){ /* this function is based on the writeHalfPort function */
	
	/*PORTB PIN1 is the RS pin on amit's kit, PORTB PIN2 is the R/W pin on amit's kit */
	
	DIO_setPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_LOW);    /* SET RS TO ZERO BECAUSE WE SEND COMMAND NOT DATA */
	DIO_setPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_LOW);    /* SET  R/W  TO ZERO BECAUSE WE WANT TO WRITE NOT TO READ */
	
	
	writeHalfPort(cmnd>>4);
	
	/*************************************************************************************************************************/
	/* Enable Pulse */   /* H => L */
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);		/* PORTB PIN3 is the enable pin on amit's kit */
	
	_delay_ms(1);
	
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
	/*************************************************************************************************************************/

	writeHalfPort(cmnd);
	
	/*************************************************************************************************************************/
	/* Enable Pulse */   /* H => L */
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	
	_delay_ms(1);
	
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
	/*************************************************************************************************************************/
	
}


void LCD_init(void){
	
	_delay_ms(35); /*delay more than 30ms as the lcd datasheet says*/ 
	
	DIO_setPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_LOW);    /* SET RS TO ZERO BECAUSE WE SEND COMMAND */
	DIO_setPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_LOW);    /* SET  R/W  TO ZERO BECAUSE WE WANT TO WRITE NOT TO READ */
	
		/* function set */
	 writeHalfPort(0b0010); /* this can be written as [ (0b00000010) or (0b0010) ]
	                        * because writeHalfPort function takes the first 4 bits(LSB) so we must maintain the order
							* by passing the MOST SIGNIFICANT 4 bits then calling it again and passing the LEAST SIGNIFICANT 4 bits
							* but here and only here at the first part of the implementation of the function LCD_init
							* we will be okay by only calling writeHalfPort once and passing 0b0010 and not calling it again to pass 0b1000
							* or even we wouldn't call LCD_sendCmnd instead of calling writeHalfPort twice and all of that is 
							* simply because in the data sheet of the LCD in the 4bit initialization specifically in the (function set part)
							* we will find that this part is formed of 3 rows instead of 2 rows like all the parts after it so 
							* in this special part we deal with the first row alone so we use writeHalfPort and only one of it not two
							* and then deals with the following 2 rows like usual with LCD_sendCmnd function 
							* instead of two writeHalfPort functions with 2 enable pulses on after each writeHalfPort function  */
/*****************************************************************************************************************/	
	/* Enable Pulse */   /* H => L */
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	
	_delay_ms(1);
	
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
/******************************************************************************************************************/
		/* function set  4 bit mode, 2 lines and 5*7 dots font  */
	LCD_sendCmnd(0b00101000);  
	
	_delay_us(45);/*  delay more than 39 micro seconds  */
	
	/*  Display on/off Control   (display on , cursor on and blink on)  */
	LCD_sendCmnd(0b00001111); 
	
	_delay_us(45);/*  delay more than 39 micro seconds*/
	
	 /* to clear the LCD */
	LCD_sendCmnd(0b00000001);
	
	_delay_ms(2);/*  delay more than 1.53 milli seconds*/
	
	/* ENTRY MODE (INCREMENT ON "IT IS A MUST" AND SHIFT DISPLAY OFF) */
	LCD_sendCmnd(0b00000110); 
	
}



void LCD_sendChar(u8 data){ /* this function is typically the same as LCD_sendCmnd except for the first line of code is inversed */
	
	DIO_setPinValue(DIO_PORTB,DIO_PIN1,DIO_PIN_HIGH);    /* SET RS TO ONE BECAUSE WE SEND DATA */
	DIO_setPinValue(DIO_PORTB,DIO_PIN2,DIO_PIN_LOW);     /* SET  R/W  TO ZERO BECAUSE WE WANT TO WRITE NOT TO READ */
	
	
	writeHalfPort(data>>4);
	
/**********************************************************************************************************************************************/	
	/* Enable Pulse */   /* H => L */
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	
	_delay_ms(1);
	
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
/**********************************************************************************************************************************************/

	writeHalfPort(data);
	
/**********************************************************************************************************************************************/	
	/* Enable Pulse */   /* H => L */
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_HIGH);
	
	_delay_ms(1);
	
	DIO_setPinValue(DIO_PORTB,DIO_PIN3,DIO_PIN_LOW);
/**********************************************************************************************************************************************/
	
}
void LCD_writeString(u8 *string){
	
	u8 Local_stringLength = 0;
	while (string[Local_stringLength] != '\0') /* to make sure that there is at least a character passed to the (LCD_writeString) function */
	{
		LCD_sendChar(string[Local_stringLength]);
		++ Local_stringLength;
	}
}

void LCD_createCustomCharacter(u8 *pattern, u8 location)
{
	
	/* use the set CGRAM address */  /* by default the LCD is on DDRAM so we send a command to write on the CGRAM */
	LCD_sendCmnd( 0x40 + (location * 8) );
	
	for(u8 i=0 ; i<8 ; i++)
	{
		
		LCD_sendChar( pattern[i] );
		
	}
	/* use the set DDRAM address to return it to its default */  
	LCD_sendCmnd(0b10000000); /* 0x80 */	/*this line is very important */
	
}

void LCD_saveInCgram(void)
{
	LCD_sendCmnd( 0x40 ); /* the address of the beginning of the CGRAM */
	
		/* PERSON */
	LCD_sendChar(0b01110);		/* we are literally lighting specific pixels and dimming specific pixels of the 5*7 dots(pixels)
								 * to form the shape that we want for example here to form the head of the person we light the 3 dots in the middle and dim the the two dots on the sides  */
	LCD_sendChar(0b01110);
	LCD_sendChar(0b00100);
	LCD_sendChar(0b11111);
	LCD_sendChar(0b10101);
	LCD_sendChar(0b00100);
	LCD_sendChar(0b01010);
	LCD_sendChar(0b01010);
	
 /*	LCD_sendCmnd( 0x48 ); */  /* we can write that line but we don't because the address is auto incremented 
							   * so when PERSON is put in location 0 the SMILE will be put automatically in location 1 etc... */
		
		/* SMILE */
	LCD_sendChar(0b00000);
	LCD_sendChar(0b00000);
	LCD_sendChar(0b01010);
	LCD_sendChar(0b00000);
	LCD_sendChar(0b00000);
	LCD_sendChar(0b10001);
	LCD_sendChar(0b01110);
	LCD_sendChar(0b00000);
	
	
	  /* LOCK */
	LCD_sendChar(0b01110);
	LCD_sendChar(0b10001);
	LCD_sendChar(0b10001);
	LCD_sendChar(0b11111);
	LCD_sendChar(0b11011);
	LCD_sendChar(0b11011);
	LCD_sendChar(0b11111);
	LCD_sendChar(0b00000);
	
	
		/*HEART*/
	LCD_sendChar(0b00000);
	LCD_sendChar(0b00000);
	LCD_sendChar(0b01010);
	LCD_sendChar(0b10101);
	LCD_sendChar(0b10001);
	LCD_sendChar(0b01110);
	LCD_sendChar(0b00100);
	LCD_sendChar(0b00000);	
	
	
	  /* volume icon */
	LCD_sendChar(0b00001);
	LCD_sendChar(0b00011);
	LCD_sendChar(0b00111);
	LCD_sendChar(0b11111);
	LCD_sendChar(0b11111);
	LCD_sendChar(0b00111);
	LCD_sendChar(0b00011);
	LCD_sendChar(0b00001);
	
	
	  /*music icon*/
	LCD_sendChar(0b00001);
	LCD_sendChar(0b00011);
	LCD_sendChar(0b00101);
	LCD_sendChar(0b01001);
	LCD_sendChar(0b01001);
	LCD_sendChar(0b01011);
	LCD_sendChar(0b11011);
	LCD_sendChar(0b11000);
	
		/*charger icon*/
	LCD_sendChar(0b01010);
	LCD_sendChar(0b01010);
	LCD_sendChar(0b11111);
	LCD_sendChar(0b10001);
	LCD_sendChar(0b10001);
	LCD_sendChar(0b01110);
	LCD_sendChar(0b00100);
	LCD_sendChar(0b00100);
	
	  /*full heart*/
	LCD_sendChar(0b00000);
	LCD_sendChar(0b00000);
	LCD_sendChar(0b01010);
	LCD_sendChar(0b11111);
	LCD_sendChar(0b11111);
	LCD_sendChar(0b01110);
	LCD_sendChar(0b00100);
	LCD_sendChar(0b00000);

			
	LCD_sendCmnd(0b10000000); /* 0x80 */ /* the datasheet says that we must return the address counter to a DD RAM location. */
}



void LCD_goTo(u8 row, u8 col)
{
	if (row == 0)
	{				/* 0x80 */
		LCD_sendCmnd(0b10000000|col); /* in the first row : the first column starts from 0x80(0b10000000) */
	}
	else if (row == 1)
	{				/* 0xc0 */
		LCD_sendCmnd(0b11000000|col); /* in the second row : the first column starts from 0xc0(0b11000000) */
	}
	
}


void LCD_clear(void)
{
	
	LCD_sendCmnd(0b00000001);
	_delay_ms(2);	/* this is so important without it the code will function normal on proteus
					   but it will not give the expected behaviour on the actual hardware similar to what happened amit's kit */
	
	
}



