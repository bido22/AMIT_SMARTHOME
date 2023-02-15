/*
 * KPD_interface.h
 *
 * Created: 9/16/2022 9:02:25 AM
 *  Author: Kimo Store
 */ 


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_


#define KPD_NOT_PRESSED    0xff		/*any type of value even if it is binary or decimal (and any value because it is just a flag) */

void KPD_getvalue(u8*returnedValue);  /* this function is based on DIO_GetPinValue */



#endif /* KPD_INTERFACE_H_ */