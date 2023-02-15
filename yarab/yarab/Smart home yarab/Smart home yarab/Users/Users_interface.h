/*
 * Users_interface.h
 *
 * Created: 15-Feb-23 10:53:30 AM
 *  Author: Marwan Yasser
 */ 


#ifndef USERS_INTERFACE_H_
#define USERS_INTERFACE_H_

#include "../STD_types.h"

typedef struct users{
	void (*sendToUser)(u8*);
	void (*recieveFromUser)(u8*);
	void (*wrongUserInput)();
	void (*newLineDisplay)();
	void (*clearDisplay)();
} User;

User admin, guest;
#endif /* USERS_INTERFACE_H_ */