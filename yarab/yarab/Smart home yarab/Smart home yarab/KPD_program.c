/*
 * KPD_program.c
 *
 * Created: 9/16/2022 9:01:58 AM
 *  Author: Kimo Store
 */ 

/* UTILES_LIB */
#include "bitmath.h"
#include "STD_types.h"
#include "ATMEGA32_REG.h"

/*  MCAL */
#include "DIO_INTERFACE.h"

/*HAL*/
#include "KPD_interface.h"
#include "KPD_config.h"


void KPD_getvalue(u8*returnedValue ){
	
/* we could have made it without array to know the benefits of using array but eventually we used arrays */	
	
 if( returnedValue == NULL )	/* to make sure it is not a wild pointer */
	 return;
	
u8 columnPins[4]={KPD_COL0_PIN,KPD_COL1_PIN,KPD_COL2_PIN,KPD_COL3_PIN}; /*size of array may differ according to the type of the keypad*/
u8 rowsPins[4]  ={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN}; /*size of array may differ according to the type of the keypad*/
		
u8 KPD_chars[4][4]= KPD_KEYS ; /*size of the 2D array may differ according to the type of the keypad*/

*returnedValue = KPD_NOT_PRESSED	;		/* to erase any garbage or old values stored */			
u8 colsCounter,rowsCounter,pinValue; /* since this function is based on DIO_GetPinValue 
									  * and we must pass an address of a variable to DIO_GetPinValue so we declared the variable pinValue */

for (colsCounter=0 ; colsCounter<4 ;++colsCounter)
{
	
	/*activate each column*/ 
	DIO_setPinValue(KPD_COLS_PORT,columnPins[colsCounter],DIO_PIN_LOW); /* we activate it by low (-ve logic) because this is a pull up resistor connection*/

	/* loop to check the row value*/
	for ( rowsCounter=0 ; rowsCounter<4 ; rowsCounter++)
	{
	
		DIO_getPinValue(KPD_ROWS_PORT,rowsPins[rowsCounter],&pinValue);
		
		if(pinValue == DIO_PIN_LOW) /* DIO_PIN_LOW means pressed (-ve logic) because this is a pull up resistor method(reverse method)*/
		{
			*returnedValue = KPD_chars[rowsCounter][colsCounter]; /* [rowsCounter][colsCounter] in that order because we focus on a column 
																   * then checks the 4 rows then transfers to the next column and checks the 4 rows etc...*/
			
			while(pinValue == DIO_PIN_LOW)    
				DIO_getPinValue(KPD_ROWS_PORT,rowsPins[rowsCounter],&pinValue);	/* we wrote this line instead of leaving the while loop empty*/														 /* so this line is considered an update for the condition of the while loop */
			
			return; /*the function will end in case it finds the value of the pressed key on the keypad*/
		}
    }
	
	/*DEACTIVATE CURRENT COLUMN*/
	DIO_setPinValue(KPD_COLS_PORT,columnPins[colsCounter],DIO_PIN_HIGH);	/* we deactivate it by low (-ve logic) because this is a pull up resistor connection*/
}
}