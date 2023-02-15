/*
 * Extras.c
 *
 * Created: 2/8/2023 7:00:57 PM
 *  Author: Mazen
 */ 

// utils
#include "ATMEGA32_REG.h"
#include "bitmath.h"
#include "STD_types.h"

#include "Extras.h"
#include "Main_config.h"



u8 comparePass(u8* pass1,u8* pass2,u8 Size)
{
	u8 passCounter=0;		/* to make sure we compare the correct size(number of characters) of the passwords */
	u8 returnValue=True;		/* we assign it by True and it will always be true unless the passwords are not identical then we assign it by False and return it indicating that the password is not correct */
	
	while(passCounter<Size)
	{
		if( *(pass1+passCounter)!=*(pass2+passCounter) )
		{
			returnValue=False;
			break;
		}
		passCounter++;
	}
	
	return returnValue;
}