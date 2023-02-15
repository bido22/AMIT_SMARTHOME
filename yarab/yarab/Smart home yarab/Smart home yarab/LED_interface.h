/*
 * LED_interface.h
 *
 * Created: 9/25/2022 5:16:10 PM
 *  Author: Mazen
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

#define LED_forward 0
#define LED_reverse 1

void LED_ON(u8 portId,u8 pinId,u8 connectionType);
void LED_OFF(u8 portId,u8 pinId,u8 connectionType);
void LED_Toggle(u8 portId,u8 pinId);


#endif /* LED_INTERFACE_H_ */