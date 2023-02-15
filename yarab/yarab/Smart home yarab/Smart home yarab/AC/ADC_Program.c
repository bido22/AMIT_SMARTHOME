/*
 * ADC_Program.c
 *
 * Created: 13-Feb-23 8:03:33 PM
 *  Author: Marwan Yasser
 */ 

#include "ADC_Config.h"
#include "ADC_Interface.h"
#include "../ATMEGA32_REG.h"
#include "../bitmath.h"

void ADC_init(){
	ADMUX = 0;
	ADMUX |= ADC_REFERENCE_VOLTAGE;
	ADCSRA = 0b00001000;
	ADCSRA |= ADC_MODE_OF_OPERATION;
	#if ADC_MODE_OF_OPERATION==ADC_AUTO_TRIGGER
		SFIOR |= ADC_AUTO_TRIGGER_SOURCE;
	#endif
	SET_BIT(ADCSRA,0);
	SET_BIT(ADCSRA,1);
	SET_BIT(ADCSRA,2);
	SET_BIT(ADCSRA,7);
}

void ADC_setChannel(u8 ADC_channel){
	ADMUX &= 0b11100000;
	ADMUX |= ADC_channel;
	CLR_BIT(DDRA, ADC_channel);
}

void ADC_start(){
	SET_BIT(ADCSRA, 6);
}

void ADC_disable(){
	CLR_BIT(ADCSRA, 7);
}

void ADC_read(u16 *digitalValue){
	if(0 == GET_BIT(ADCSRA, 7))
		ADC_init();
	ADC_start();
	while(1 == GET_BIT(ADCSRA,6));
	*digitalValue = ADC_u16;
}

void ADC_readChannel(u8 ADC_channel, u16 *digitalValue){
	if(ADC_channel < 0 || ADC_channel > 7 || digitalValue == NULL)
		return;
	if(0 == GET_BIT(ADCSRA, 7))
		ADC_init();
	ADC_setChannel(ADC_channel);
	ADC_start();
	while(0 == GET_BIT(ADCSRA,4));
	*digitalValue = ADC_u16;
}

void ADC_startAutoTrigger(u8 ADC_channel){
	if(ADC_channel < 0 || ADC_channel > 7)
		return;
	if(0 == GET_BIT(ADCSRA, 7))
		ADC_init();
	ADC_setChannel(ADC_channel);
	ADC_start();
}

void ADC_getAnalogValue(u16 digitalValue, u16 *analogValue){
	#if ADC_REFERENCE_VOLTAGE==AREF
		*analogValue = ((u32)digitalValue) * ADC_REFERENCE_VOLTAGE_VALUE / 1023;
	#elif ADC_REFERENCE_VOLTAGE==AVCC
		*analogValue = ((u32)digitalValue) * 5000 / 1023;
	#elif ADC_REFERENCE_VOLTAGE==INTERNAL_VOLTAGE
		*analogValue = ((u32)digitalValue) * 2560 / 1023;
	#endif
}

#if ADC_MODE_OF_OPERATION==ADC_AUTO_TRIGGER

	static void(*ADCpCallBack)(void) = NULL;
	
	void ADC_ADCSetCallBack(void(*ptr)(void)){
		ADCpCallBack = ptr;
	}
	
	void __vector_16(void) __attribute__ ((signal));
	void __vector_16(void)
	{
		if(ADCpCallBack != NULL){
			ADCpCallBack();
		}
		}

#endif