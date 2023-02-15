/*
 * UART_interface.h
 *
 * Created: 10/15/2022 2:42:13 AM
 *  Author: meow
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_init(void);
void UART_sendString(u8* string);
void UART_send(u8 data);
void UART_receive(u8* returnedData);



#endif /* UART_INTERFACE_H_ */