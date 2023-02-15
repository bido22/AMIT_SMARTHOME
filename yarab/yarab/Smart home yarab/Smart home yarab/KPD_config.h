/*
 * KPD_config.h
 *
 * Created: 9/16/2022 9:02:55 AM
 *  Author: Kimo Store
 */ 


#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

           /*  the instructor advices us at least right now not to connect many things on the kit together so we specially chose these ports
		    *  and pins because we can unplug the LCD and the H-bridge from amit's kit */
		   
		   /* MACROS FOR KPD COLUMNS PORTS & PINS CONFIGURATION */
		   
#define KPD_COLS_PORT       DIO_PORTB	/* we should change the ports and pins if we used this driver in different projects with different ports and pins so our driver is more generic */
#define KPD_COL0_PIN		DIO_PIN4
#define KPD_COL1_PIN		DIO_PIN5
#define KPD_COL2_PIN		DIO_PIN6
#define KPD_COL3_PIN		DIO_PIN7

		   /* MACROS FOR KPD ROWS PORTS & PINS CONFIGURATION */		 

#define KPD_ROWS_PORT       DIO_PORTC	/* we should change the ports and pins if we used this driver in different projects with different ports and pins so our driver is more generic */
#define KPD_ROW0_PIN		DIO_PIN3
#define KPD_ROW1_PIN		DIO_PIN4
#define KPD_ROW2_PIN		DIO_PIN5
#define KPD_ROW3_PIN		DIO_PIN6


#define KPD_KEYS			{'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'} /* this may differ from keypad to another */


#endif /* KPD_CONFIG_H_ */