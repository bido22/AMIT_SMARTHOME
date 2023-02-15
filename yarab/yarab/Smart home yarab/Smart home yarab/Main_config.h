/*
 * Main_config.h
 *
 * Created: 2/8/2023 4:13:13 PM
 *  Author: Mazen
 */ 


#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_


/* pin config */			/* indicator */
#define False 0
#define True 1

/* password configs */
#define NOT_STORED   0xFF		/* because initially in the internal EEPROM the initial values in the addresses are 0xFF */

#define PASS_SIZE       4		/* if we change the number of characters of the password later */
#define TRIES_ALLOWED   3		/* those are the number of tries allowed for the admin or guest to enter wrong password */

#define PASS_NOT_SET 0xFF
#define PASS_SET     0x01

						/* this (u16)1000
						   is another way
						   of writing the address
						   we could have used
					       hexadecimal or binary */
#define ADMIN_PASS_STATUS_ADDRESS (u16)1000		/* this is to know if we run the code for the first time so we make the code ask the user to set the admin password and the guest password or it is not the first time so we make the system ask the user to select admin mode or guest mode and upon his selection we ask him to enter the already stored password */
#define GUEST_PASS_STATUS_ADDRESS (u16)1001

#define EEPROM_ADMIN_ADDRESS      (u16)1002		/* this is the address where the password of the admin is stored and we separated it by 4 bytes apart from the guest mode
												 because we made our passwords 4 charachters and we increment when we use it to ditribute the 4 characters on the 4 addresses(4bytes)   */
#define EEPROM_GUEST_ADDRESS      (u16)1006

#define LOGIN_BLOCKED_ADDRESS     (u16)1010


/* login configs */

#define NO_MODE 0
#define ADMIN   1
#define GUEST   2

#define CHECK_ADMIN_MODE        '0'		/* a zero between single quotations in which its ascii is 48 so we can send it on the mobile by simply typing zero however if we chose 0 without single quotations it will require that on the mobile we hold on the M1 button and select HEX on the (edit mode) section and write 0 in the (value) section */
#define CHECK_GUEST_MODE        '1'
/* menu configs */

#define ROOM1_MENU           '2'
#define ROOM2_MENU           '3'
#define ROOM3_MENU           3
#define ROOM4_MENU           4
#define ROOM5_MENU			 5
#define ROOM6_MENU			 6
#define MAIN_MENU            0
#define MORE_MENU            '4'
#define DOOR_MENU			 '1'

/* select configs */
// ADMIN OPTIONS
#define SELECT_DOOR				   '1'
#define SELECT_ROOM1_ADMIN         '2'
#define SELECT_ROOM2_ADMIN         '3'
#define ADMIN_MORE_OPTION		   '4'
// MORE MENU (ADMIN)
#define SELECT_ROOM3_ADMIN         '1'
#define SELECT_ROOM4_ADMIN		   '2'
#define SELECT_ROOM5_ADMIN		   '3'
#define SELECT_ROOM6_ADMIN		   '4'
// GUEST OPTIONS 
#define SELECT_ROOM1_GUEST		   '1'
#define SELECT_ROOM2_GUEST         '2'
#define SELECT_ROOM3_GUEST         '3'
#define GUEST_MORE_OPTIONS		   '4'
// MORE MENU (GUEST)
#define SELECT_ROOM4_GUEST		   '1'
#define SELECT_ROOM5_GUEST         '2'
#define SELECT_ROOM6_GUEST         '3'
#define GUEST_RETURN_OPTION 	   '4'
/* ROOM ACTIONS */
#define ROOM_OFF_OFF '1'
#define ROOM_OFF_ON  '2'
#define ROOM_ON_ON	 '1'
#define ROOM_ON_OFF  '2'
/* ROOM LIGHTS */
#define ROOM1_LIGHT  DIO_PORTC,DIO_PIN2
#define ROOM2_LIGHT  DIO_PORTC,DIO_PIN7
#define ROOM3_LIGHT	 DIO_PORTD,DIO_PIN3
#define ROOM4_LIGHT  DIO_PORTB,DIO_PIN0
#define ROOM5_LIGHT	 DIO_PORTD,DIO_PIN6
#define ROOM6_LIGHT  DIO_PORTD,DIO_PIN6

#endif /* MAIN_CONFIG_H_ */