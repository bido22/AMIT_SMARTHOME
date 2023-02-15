/*
 * Admin_Interface.h
 *
 * Created: 15-Feb-23 10:52:04 AM
 *  Author: Marwan Yasser
 */ 


#ifndef ADMIN_INTERFACE_H_
#define ADMIN_INTERFACE_H_

#include "../../STD_types.h"

void Admin_sendString(u8* adminString);
void Admin_newLine();
void Admin_recieveInput(u8* adminInput);
void Admin_wrongInput();
void Admin_clearDisplay();

#endif /* ADMIN_INTERFACE_H_ */