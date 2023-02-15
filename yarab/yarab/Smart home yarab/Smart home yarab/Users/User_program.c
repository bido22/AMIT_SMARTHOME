/*
 * User_program.c
 *
 * Created: 15-Feb-23 12:44:14 PM
 *  Author: Marwan Yasser
 */ 

#include "Users_interface.h"
#include "Admin/Admin_Interface.h"
#include "Guest/Guest_interface.h"


User admin = {&Admin_sendString, &Admin_recieveInput, &Admin_wrongInput, &Admin_newLine, &Admin_clearDisplay};
User guest = {&Guest_sendString, &Guest_recieveInput, &Guest_wrongInput, &Guest_newLine, &Guest_clearDisplay};