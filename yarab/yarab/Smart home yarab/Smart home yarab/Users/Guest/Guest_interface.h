/*
 * Guest_interface.h
 *
 * Created: 15-Feb-23 10:52:49 AM
 *  Author: Marwan Yasser
 */ 


#ifndef GUEST_INTERFACE_H_
#define GUEST_INTERFACE_H_

#include "../../STD_types.h"

void Guest_sendString(u8* guestString);
void Guest_newLine();
void Guest_recieveInput(u8* guestInput);
void Guest_wrongInput();
void Guest_clearDisplay();

#endif /* GUEST_INTERFACE_H_ */