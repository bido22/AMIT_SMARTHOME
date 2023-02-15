/*
 * ADC_Interface.h
 *
 * Created: 13-Feb-23 8:03:52 PM
 *  Author: Marwan Yasser
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "../STD_types.h"

/* ADC INPUT MODES */
#define ADC_SINGLE_ENDED_INPUT					0
#define ADC_POSITIVE_DIFFERENTIAL_INPUT			1
#define ADC_NEGATIVE_DIFFERENTIAL_INPUT			2

/* ADC MODES OF OPERATION */
#define ADC_SINGLE_CONVERSION					0b00000000
#define ADC_AUTO_TRIGGER						0b00100000

/* ADC AUTO TRIGGER SOURCE */
#define FREE_RUNNING							0b00000000
//7AGAT TANYA

/* ADC REFERENCE VOLTAGES */
#define AREF									0b00000000   //Use an external reference voltage
#define AVCC									0b01000000	//Use internal VCC voltage
#define INTERNAL_VOLTAGE						0b11000000	//Use internal 2.56V Voltage Reference with external capacitor at AREF pin

/* METHODS */
void ADC_init();
void ADC_read(u16 *digitalValue);
void ADC_readChannel(u8 ADC_channel, u16 *digitalValue);
void ADC_startAutoTrigger(u8 ADC_channel);
void ADC_getAnalogValue(u16 digitalValue, u16 *analogValue);
void ADC_disable();

#if ADC_MODE_OF_OPERATION==ADC_AUTO_TRIGGER
	void ADC_ADCSetCallBack(void(*ptr)(void));
#endif


#endif /* ADC_INTERFACE_H_ */