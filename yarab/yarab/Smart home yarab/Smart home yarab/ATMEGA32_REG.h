/*
 * ATMEGA32_REG.h
 *
 * Created: 9/4/2022 9:54:37 PM
 *  Author: Mazen
 */ 


#ifndef ATMEGA32_REG_H_
#define ATMEGA32_REG_H_


			/* DIO REGISTERS*/
/* DATA DIRCTION REGISTERS */
#define DDRA           (*(volatile u8*)0x3A)
#define DDRB           (*(volatile u8*)0x37)
#define DDRC           (*(volatile u8*)0x34)
#define DDRD           (*(volatile u8*)0x31)


/* OUTPUT REGISTERS */
#define PORTA          (*(volatile u8*)0x3B)
#define PORTB          (*(volatile u8*)0x38)
#define PORTC          (*(volatile u8*)0x35)
#define PORTD          (*(volatile u8*)0x32)


/* INPUT REGISTERS */
#define PINA           (*(volatile u8*)0x39)
#define PINB           (*(volatile u8*)0x36)
#define PINC           (*(volatile u8*)0x33)
#define PIND           (*(volatile u8*)0x30)

				/* Interrupts */

// MCU Control Register
#define MCUCR            (*(volatile u8*)0x55)

// MCU Control and Status Register
#define MCUCSR           (*(volatile u8*)0x54)

// General Interrupt Control Register
#define GICR             (*(volatile u8*)0x5B)

// General Interrupt Flag Register
#define GIFR             (*(volatile u8*)0x5A)

// Status Register
#define SREG             (*(volatile u8*)0x5F)
 /* ADC */

// ADC Multiplexer Selector Register
#define ADMUX			 (*(volatile u8*)0x27)

// ADC Control and Status Register
#define ADCSRA			 (*(volatile u8*)0x26)

//ADC Data Registers 
#define ADCL			 (*(volatile u8*)0x24)
#define ADCH			 (*(volatile u8*)0x25)
#define ADC_u16			 (*(volatile u16*)0x24) // ADCH + ADCL

// Special Function IO Register 
#define SFIOR			 (*(volatile u8*)0x50)

/* TIMERS REGISTERS*/

#define TCNT0  *(volatile u8*)0x52
#define TCCR0  *(volatile u8*)0x53
#define TIMSK  *(volatile u8*)0x59
#define OCR0   *(volatile u8*)0x5C

#define TCCR1A *(volatile u8*)0x4F
#define TCCR1B *(volatile u8*)0x4E
#define ICR1   *(volatile u16*)0x46
#define OCR1A  *(volatile u16*)0x4A
#define OCR1B  *(volatile u16*)0x48
 
 					/* uart */
				 
//USART I/O Data Register – UDR
#define UDR	(*(volatile u8*)0x2C)
//USART Control and Status Register A – UCSRA
#define UCSRA	(*(volatile u8*)0x2B)
//USART Control and Status Register B – UCSRB
#define UCSRB	(*(volatile u8*)0x2A)
//USART Control and Status Register C – UCSRC
#define UCSRC	(*(volatile u8*)0x40)
//USART Baud Rate Registers – UBRRL and UBRRH
#define UBRRL	(*(volatile u8*)0x29)
#define UBRRH	(*(volatile u8*)0x40)

					/* spi */
			
//SPI Control Register – SPCR
#define SPCR	(*(volatile u8*)0x2D)
//SPI Status Register – SPSR
#define SPSR	(*(volatile u8*)0x2E)
//SPI Data Register – SPDR
#define SPDR	(*(volatile u8*)0x2F)
					/* I2C */
// TWI Bit Rate Register
#define TWBR          (*(volatile u8*)0x20)

// TWI Control Register
#define TWCR          (*(volatile u8*)0x56)

// TWI Status Register
#define TWSR          (*(volatile u8*)0x21)

// TWI Data Register
#define TWDR          (*(volatile u8*)0x23)

// TWI (Slave) Address Register
#define TWAR          (*(volatile u8*)0x22)

/* EEPROM */

#define EEARL     *((volatile u8*)0x3E)
#define EEARH     *((volatile u8*)0x3F)
#define EEDR      *((volatile u8*)0x3D)
#define EECR      *((volatile u8*)0x3C)
#define EEAR_u16  *((volatile u16*)0x3E)





#endif /* ATMEGA32_REG_H_ */