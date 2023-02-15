/*
 * Rooms_program.c
 *
 * Created: 15-Feb-23 7:07:59 PM
 *  Author: Marwan Yasser
 */ 

#include "Rooms_Interface.h"
#include "../Timer/TMR_Interface.h"
#include "../LED_interface.h"
#include "../DIO_INTERFACE.h"
#include "../Users/Users_interface.h"

void Room_lightToggle(Room *room){
	room -> lightState = !(room -> lightState);
	DIO_setPinDirection(room -> lightPortID, room -> lightPinId, DIO_PIN_OUTPUT);
	if(room -> dimState)
		TMR_setPWM(50, room -> lightState * 100);
	else
		LED_Toggle(room -> lightPortID, room -> lightPinId);
}

void Room_lightDim(Room *room, User *user){
	if(!(room -> dimState) || !(room -> lightState))
		return;
	u8 dimValue;
	user -> clearDisplay();
	user -> sendToUser("Dim Value");
	user -> newLineDisplay();
	user -> sendToUser("1:75 2:50 3:25");
	user -> recieveFromUser(&dimValue);
	dimValue = (dimValue > '3' || dimValue < '1')? 0 : dimValue - 0x30;
	TMR_setPWM(50, 100 - dimValue * 25);
}

void Room_showStatus(Room *room, User *user){
	u8 statusDisplay[16] = "ROOM  STATUS:   ";
	statusDisplay[4] = room -> roomId + 0x30;
	u8 userInput;
	do
	{
		user -> clearDisplay();
		if(room -> lightState){
			statusDisplay[13] = 'O';
			statusDisplay[14] = 'N';
			statusDisplay[15] = ' ';
		}
		else{
			statusDisplay[13] = 'O';
			statusDisplay[14] = 'F';
			statusDisplay[15] = 'F';
		}
		user -> sendToUser(statusDisplay);
		user -> newLineDisplay();
		
		if(room -> dimState && room -> lightState)
			user -> sendToUser("1:TG 2:Dim 0:RET");
		else
			user -> sendToUser("1:Toggle 0:RET");

		user -> recieveFromUser(&userInput);
		if(userInput == '1')
			Room_lightToggle(room);
		else if(userInput =='0')
			break;
		else if(userInput == '2')
			Room_lightDim(room, user);
		else
			user -> wrongUserInput();
	} while (1);
}

Room room1 = {1, DIM_OFF, LIGHT_OFF, DIO_PORTC, DIO_PIN2};
Room room2 = {2, DIM_OFF, LIGHT_OFF, DIO_PORTC, DIO_PIN7};
Room room3 = {3, DIM_OFF, LIGHT_OFF, DIO_PORTD, DIO_PIN3};
Room room4 = {4, DIM_OFF, LIGHT_OFF, DIO_PORTB, DIO_PIN0};
Room room5 = {5, DIM_OFF, LIGHT_OFF, DIO_PORTD, DIO_PIN6};
Room room6 = {6, DIM_ON, LIGHT_OFF, DIO_PORTD, DIO_PIN5};