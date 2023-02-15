/*
 * LCD_interface.h
 *
 * Created: 9/10/2022 10:21:09 AM
 *  Author: Kimo Store
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void writeHalfPort(u8 value);	/* it is a function that copies the lsb 4 bits and puts them in PORTA pin4,5,6,7 */
void LCD_sendCmnd(u8 cmnd);				/* it is basically a 2 writeHalfPort functions and after each function of them there is an enable pulse  */
void LCD_init(void);


void LCD_sendChar(u8 data);     /* sometimes instead of naming this function LCD_sendChar we name it LCD_sendData */
void LCD_writeString(u8 *string);


void LCD_saveInCgram(void);									/* this function contains 8 custom characters I created */

void LCD_createCustomCharacter(u8 *pattern, u8 location);   /* this function is used for creating a custom character 
															 * that is not found in the LCD_saveInCgram function    */


void LCD_goTo(u8 row, u8 col); /*this function used to display something in a specific place on the LCD not on the default place*/

void LCD_clear(void);


#endif /* LCD_INTERFACE_H_ */