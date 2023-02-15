/*
 * Smart home yarab.c
 *
 * Created: 2/8/2023 3:19:58 PM
 * Author : Mazen
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Main_config.h"
// utils 
#include "ATMEGA32_REG.h"
#include "bitmath.h"
#include "STD_types.h"

// mcal 
#include "DIO_INTERFACE.h"
#include "UART_interface.h"
#include "EEPROM_interface.h"
#include "Timer/TMR_Interface.h"

// hal 
#include "LCD_config.h"
#include "LCD_interface.h"
#include "KPD_interface.h"
#include "KPD_config.h"
#include "LED_interface.h"


#include "Extras.h"
#include "Users/Users_interface.h"
#include "Room/Rooms_Interface.h"

void tempCheck(){
	u16 val = ADC_u16;
	static u8 status = 0;
	if(val > 51 && status == 0){
		DIO_setPinValue(DIO_PORTA,DIO_PIN2,1);
		status = 1;
	}
	else if(val < 51 && status == 1){
		DIO_setPinValue(DIO_PORTA,DIO_PIN2,0);
		status = 0;
	}
}


int main(void)
{
	/* important variables */
	u8 loginMode = NO_MODE;
	u8 blockMode = False;
	u8 showMenu = MAIN_MENU;
	User currentUser = guest;
/********************************************* INITIALIZATION *******************************************************/
	/***********************************************	Keypad		***********************************************/
	
	/*columns*/
	DIO_setPinDirection(DIO_PORTB,DIO_PIN4,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN6,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTB,DIO_PIN7,DIO_PIN_OUTPUT);
	
	/*rows*/
	DIO_setPinDirection(DIO_PORTC,DIO_PIN3,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTC,DIO_PIN4,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTC,DIO_PIN5,DIO_PIN_INPUT);
	DIO_setPinDirection(DIO_PORTC,DIO_PIN6,DIO_PIN_INPUT);
	
	/*pull up resistors activation*/
	DIO_setInputPinResistance(DIO_PORTC,DIO_PIN3);
	DIO_setInputPinResistance(DIO_PORTC,DIO_PIN4);
	DIO_setInputPinResistance(DIO_PORTC,DIO_PIN5);
	DIO_setInputPinResistance(DIO_PORTC,DIO_PIN6);
	
	/*****************************************************************************************************************************************/
	/***********************************************				LCD				    ******************************************************/
	
	/* 4 DATA PINS */
	DIO_setPinDirection(DIO_PORTA,DIO_PIN4,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN5,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN6,DIO_PIN_OUTPUT);
	DIO_setPinDirection(DIO_PORTA,DIO_PIN7,DIO_PIN_OUTPUT);
	
	/* 3 CONTROL PINS */
	DIO_setPinDirection(DIO_PORTB,DIO_PIN1,DIO_PIN_OUTPUT); /*RS*/
	DIO_setPinDirection(DIO_PORTB,DIO_PIN2,DIO_PIN_OUTPUT); /*R/W*/
	DIO_setPinDirection(DIO_PORTB,DIO_PIN3,DIO_PIN_OUTPUT); /*E*/


	LCD_init();
	/**********************************************************************************************************************************/
	
	
	UART_init();  // initialize uart
	
	 /***********************************************				ADC				    ******************************************************/
	 SET_BIT(SREG, 7);
	 ADC_ADCSetCallBack(&tempCheck);
	 DIO_setPinDirection(DIO_PORTA,DIO_PIN1,DIO_PIN_INPUT);
	 DIO_setPinDirection(DIO_PORTA,DIO_PIN2,DIO_PIN_OUTPUT);
	 ADC_startAutoTrigger(/*select the channel*/1);
	
/********************************************************************************************************************/
	/* print welcome screen */
	UART_sendString("Welcome to smart home system\r\n");			/* the ( \r\n ) to go to a new line on the screen of our mobile or PC or the virtual terminal on proteus */

	/* check if we login for the first time or this is not the first time and we already set passwords */
	u8 AdminReturnedData,GuestReturnedData;
	
	EEPROM_Read_Byte(ADMIN_PASS_STATUS_ADDRESS,&AdminReturnedData);
	EEPROM_Read_Byte(GUEST_PASS_STATUS_ADDRESS,&GuestReturnedData);
	
	if( (AdminReturnedData == PASS_NOT_SET) || (GuestReturnedData == PASS_NOT_SET) ) // if this condition is true this means that we haven't set one of these passwords and this is the first time we run our system
	{
			
		/*************************************************** setting admin passwrod ******************************************************/
			UART_sendString("Login for first time\r\n");
			UART_sendString("Set admin password\r\n");
			UART_sendString("Admin pass:");					
			
			u8 passCounter=0;	/* to make sure the user enters only the number of characters decided in the Main_config.h */
			u8 receivedAdminPassLetter,receivedGuestPassLetter;	/* those two variable each one of them acts as a holder or carrier that transmits the value from place to another but a variable for admin password and a variable for guest password */
			
			while(passCounter<PASS_SIZE)
			{
				UART_receive(&receivedAdminPassLetter);			/* the user enters the number on the mobile and we put it in the variable(receivedAdminPassLetter) */
				UART_send(receivedAdminPassLetter);				/* then we send this number to display it on the mobile to give such a good experience */
				EEPROM_Write_Byte(EEPROM_ADMIN_ADDRESS+passCounter,receivedAdminPassLetter);	/* this is the increment we were talking about in the Main_config.h */
																								/* and here we are storing the number in the internal EEPROM in the EEPROM_ADMIN_ADDRESS  */
				passCounter++;
			}
			EEPROM_Write_Byte(ADMIN_PASS_STATUS_ADDRESS,PASS_SET); /* here we update the ADMIN_PASS_STATUS_ADDRESS to make the system know later that we already set the password of the admin mode and to make the system not ask to set the password but to enter the admin password (if the admin mode was selected)  */

		/************************************************ setting guest passwrod ***************************************************/
	
			passCounter=0; /* to use this variable more than once instead of using too many variables */
			UART_sendString("\r\nSet guest pass\r\n");
			UART_sendString("Guest pass:");
			while(passCounter<PASS_SIZE)
			{																			/*the same method as we did above
																						 while setting the admin password*/
				UART_receive(&receivedGuestPassLetter);
				UART_send(receivedGuestPassLetter);
				EEPROM_Write_Byte(EEPROM_GUEST_ADDRESS+passCounter,receivedGuestPassLetter);
				passCounter++;
			}
			EEPROM_Write_Byte(GUEST_PASS_STATUS_ADDRESS,PASS_SET);
		/*****************************************************************************************/		
			UART_sendString("\r\nPass saved");
			EEPROM_Write_Byte(LOGIN_BLOCKED_ADDRESS,False);  /* since it is the first time to run the project( setting the passwords of admin mode and guest mode ) then logically the user can't be blocked so we put FALSE LOGIN_BLOCKED_ADDRESS */
	}
	else 
	{			/* we will enter the else when it is not the first time to run the project(if we already set the passwords of the admin and the guest) */
			u8 blockModeIndicator;
			EEPROM_Read_Byte(LOGIN_BLOCKED_ADDRESS,&blockModeIndicator);
			blockMode=blockModeIndicator;
	}
	
/**********************************************************************************************************************************************************************************************************************/	

    while (1) 
    {
		u8 passTries=0;
		while(loginMode==NO_MODE)
		{
			if(blockMode==True)
			{
				UART_sendString("\r\nLogin Blocked\r\n");
				
				// open buzzer
				DIO_setPinDirection(DIO_PORTA,DIO_PIN3,DIO_PIN_OUTPUT);
				DIO_setPinValue(DIO_PORTA,DIO_PIN3,DIO_PIN_HIGH);
				
				// turn off block mode to run normal code after reset(or after turnning on or off the kit)
				EEPROM_Write_Byte(LOGIN_BLOCKED_ADDRESS,False);
				while(1); /* if you are blocked then the buzzer will be forever on until the reset or the power on/off button on amit's kit */
			}
			
			/************** we will reach these lines of code when the user is not blocked I mean when (blockMode==False) ********************/
			
			UART_sendString("\r\nSelect Mode:\r\n");
			UART_sendString("0:Admin\r\n1:Guest");
			
			u8 Mode;
			UART_receive(&Mode);
			if(Mode != CHECK_ADMIN_MODE && Mode != CHECK_GUEST_MODE) /* to make the user enters 0 or 1 only and not other values */
			{
				UART_sendString("\r\nWrong input\r\n"); /* this is the output if the user enters any value other than 0 or 1 */
			}
			
			u8 pass_counter=0;
			u8 pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
			u8 storedPass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
				
			switch(Mode)
			{
				/************************************************* Admin Login *******************************************/
				case CHECK_ADMIN_MODE:	/* if the user entered 0 which is the admin mode */
						while(loginMode != ADMIN) // this is to repeat login for admin mode in case of wrong password  where at first time the loginMode = NO_MODE and if the admin entered the correct password the loginMode will be updated and will be loginMode = ADMIN  however if he entered a wrong password the loginMode will still be loginMode = NO_MODE
						{
							UART_sendString("\r\nAdmin Mode\r\n");
							UART_sendString("Enter password:");
							pass_counter=0;
							while(pass_counter<PASS_SIZE)
							{
								u8 AdminPassLetter;
								UART_receive(&AdminPassLetter);
								UART_send(AdminPassLetter);
								pass[pass_counter]=AdminPassLetter;
								EEPROM_Read_Byte(EEPROM_ADMIN_ADDRESS+pass_counter,&storedPass[pass_counter]);
								pass_counter++;
							}
								/* compare the two arrays one that contains the entered password and one contains the correct already stored(set) password */
							if(comparePass(pass,storedPass,PASS_SIZE) == True)
							{
								loginMode=ADMIN;
								currentUser = admin;
								passTries=0;
								UART_sendString("\r\nRight Password\r\n");
								UART_sendString("you are on Admin Mode\r\n");
							}
							else /* we will not enter the else unless the two arrays (passwords) are not identical */
							{
								passTries++;
								loginMode=NO_MODE;
								UART_sendString("\r\nWrong pass\r\n");
								UART_sendString("Tries left:");
								UART_send(TRIES_ALLOWED-passTries+'0'); /* we wrote (+'0') because we want to display the numbers from 0 to 9 that their ascii codes ranges from 48 to 57
																		 and (TRIES_ALLOWED) are 3 not '3' so it will be understood as the character whose ascii is 3 not number 3
																		 and same goes for the variable (passTries) */
								if(passTries>=TRIES_ALLOWED)
								{
									EEPROM_Write_Byte(LOGIN_BLOCKED_ADDRESS,True);
									blockMode=True;
									break;
								}
							}
						}
				break;
				/************************************************ Guest Login *******************************************************/
				case CHECK_GUEST_MODE:  /* if the user entered 0 which is the guest mode */
				while(loginMode != GUEST)
				{
					pass_counter=0;
					u8 keystate=KPD_NOT_PRESSED;
					LCD_goTo(0,0);
					LCD_writeString("Enter the");
					LCD_goTo(1,0);
					LCD_writeString("four characters");
					while(pass_counter<PASS_SIZE)
					{
						KPD_getvalue(&keystate);
						EEPROM_Read_Byte(EEPROM_GUEST_ADDRESS+pass_counter,&storedPass[pass_counter]);

						if(keystate != KPD_NOT_PRESSED)
						{
							
							LCD_goTo(0,pass_counter);
							if(pass_counter==0){LCD_clear();}
							LCD_sendChar(keystate);
							_delay_ms(300);
							pass[pass_counter]=keystate;

							LCD_goTo(0,pass_counter);  /*we are able to overwrite the number by astrisk to look more professional*/
							LCD_sendChar('*');
							pass_counter++;
						}
						
						
					}
							
							/* compare pass */
							if( comparePass(pass,storedPass,PASS_SIZE)==True )
							{
								loginMode=GUEST;
								passTries=0;
								LCD_clear();
								LCD_goTo(0,0);
								LCD_writeString("RIGHT PASSWORD");
							}
							else
							{
								passTries++;
								loginMode=NO_MODE;
								u8 triesleft = TRIES_ALLOWED-passTries+'0';
								LCD_clear();
								LCD_goTo(0,0);
								LCD_writeString("WRONG PASSWORD");
								_delay_ms(2000);
								LCD_clear();
								LCD_writeString("Tries left:");
								LCD_goTo(1,0);
								LCD_sendChar(TRIES_ALLOWED-passTries+'0');
								_delay_ms(2000);

								if(passTries>=TRIES_ALLOWED)
								{
									EEPROM_Write_Byte(LOGIN_BLOCKED_ADDRESS,True);
									blockMode=True;
									break;
								}
							}
						}
				break;	
			} /* this is the end of the switch(Mode) */
			
		
		} /* this is the end of while(loginMode==NO_MODE)  */
		u8 actionbutton;
		u8 key_pressed=KPD_NOT_PRESSED;
		u8 ledState;
		switch(showMenu)
		{
			case MAIN_MENU:
				currentUser.clearDisplay();
				currentUser.sendToUser("1:Door 2:Room1");
				currentUser.newLineDisplay();
				currentUser.sendToUser("3:Room2 4:More");
				
				currentUser.recieveFromUser(&actionbutton);
				showMenu = (actionbutton > '4' || actionbutton < '1')? 0 : actionbutton;
			break;	
			
			case MORE_MENU:
				currentUser.clearDisplay();
				currentUser.sendToUser("1:Room3 2:Room4");
				currentUser.newLineDisplay();
				currentUser.sendToUser("3:Room5 4:Room6");
				
				currentUser.recieveFromUser(&actionbutton);
				actionbutton += 2;
				showMenu = (actionbutton > '6' || actionbutton < '3')? 0 : actionbutton - 0x30;
				
			break;
			case ROOM1_MENU:
				Room_showStatus(&room1, &currentUser);
				showMenu=MAIN_MENU;
				break;
			case ROOM2_MENU:
				Room_showStatus(&room2, &currentUser);
				showMenu=MAIN_MENU;
				break;
			
			case ROOM3_MENU:
				Room_showStatus(&room3, &currentUser);
				showMenu=MAIN_MENU;
				break;
			case ROOM4_MENU:
				Room_showStatus(&room4, &currentUser);
				showMenu=MAIN_MENU;
				break;
			case ROOM5_MENU:
				Room_showStatus(&room5, &currentUser);
				showMenu=MAIN_MENU;
				break;
			// DIMMER
			
			case ROOM6_MENU:
				Room_showStatus(&room6, &currentUser);
				showMenu=MAIN_MENU;
				break;
			
			//DOOR
			case DOOR_MENU:
				if(loginMode==ADMIN)
				{
					UART_sendString("1:open door  2: close door  3:RET");
					while(1){
						UART_receive(&actionbutton);
						if(actionbutton == '1'){
							TMR_setPWM(50, 50);
							break;
						}
						else if(actionbutton == '2'){
							TMR_setPWM(50, 0);
							break;
						}
						else if(actionbutton == '3'){}
					}
				}
				showMenu=MAIN_MENU;
				break;
		
		}
    } /* this is the end of while(1) */
} /* this is the end of int main(void) */

