/*
 * Room_Interface.h
 *
 * Created: 15-Feb-23 7:00:02 PM
 *  Author: Marwan Yasser
 */ 


#ifndef ROOMS_INTERFACE_H_
#define ROOMS_INTERFACE_H_

#include "../STD_types.h"
#include "../Users/Users_interface.h"

typedef struct rooms{
	u8 roomId;
	u8 dimState;
	u8 lightState;
	u8 lightPortID;
	u8 lightPinId;
}Room;

Room room1, room2, room3, room4, room5, room6;

#define LIGHT_OFF 0
#define LIGHT_ON  1

#define DIM_OFF   0
#define DIM_ON    1

void Room_lightToggle(Room *room);
void Room_lightDim(Room *room, User *user);
void Room_showStatus(Room *room, User *user);


#endif /* ROOMS_INTERFACE_H_ */