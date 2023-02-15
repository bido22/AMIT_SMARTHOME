/*
 * TMR_Interface.h
 *
 * Created: 10/6/2022 4:44:21 PM
 *  Author: Marwan Yasser
 */ 


#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define TMR_CLOCK_OFF				 0
#define TMR_CLOCK_PRESCALAR_1		 1
#define TMR_CLOCK_PRESCALAR_8		 8
#define TMR_CLOCK_PRESCALAR_64		 64
#define TMR_CLOCK_PRESCALAR_256		 256
#define TMR_CLOCK_PRESCALAR_1024	 1024
#define TMR_CLOCK_EXT_FALLING_EDGE   6
#define TMR_CLOCK_EXT_RISING_EDGE    7

#define TMR_TIMER0_NORMAL_MODE			   0b00000000
#define TMR_TIMER0_PHASE_CORRECT_PWM_MODE  0b01110000
#define TMR_TIMER0_CTC_MODE			       0b00001000
#define TMR_TIMER0_FAST_PWM_MODE		   0b01101000 

#define TMR_TIMER1_NORMAL_MODE			   0
#define TMR_TIMER1_CTC_MODE			       4
#define TMR_TIMER1_ICR_FAST_PWM_MODE	   14

void TMR_setTimer(u32 desiredTime, u32* number_of_flags);
void TMR_stopTimer();
#if TMR_TIMER0_OPERATING_MODE == TMR_TIMER0_FAST_PWM_MODE || TMR_TIMER0_OPERATING_MODE == TMR_TIMER0_PHASE_CORRECT_PWM_MODE
	void TMR_setPWM0(u8 TMR_timer0_PWM_dutyCycle);
	void TMR_stopPWM0();
#endif

void TMR_setPWM(u32 TMR_timer1_PWM_frequency, u8 TMR_timer1_PWM_dutyCycle);
void TMR_stopPWM();

#endif /* TMR_INTERFACE_H_ */