#include "fc.h"

#include <avr/interrupt.h>

namespace fc {
		
	uint16_t lastCapture = 0;
	uint16_t pulseWidth = 0;
	
	ISR(TIMER1_CAPT_vect) {
		pulseWidth = ICR1 - lastCapture;
		lastCapture = ICR1;
	}
	
	void init() {
		DDRB &= ~(1<<PORTB0); //set port PB0 as input
		TCCR1A = 0x00;
		TCCR1B = 0b10000010; //ICNC1 = 1 (noise canceler); ICES1 = 0 (falling edge); WGM13, WGM12 = 00; CS12, CS11, CS10 = 010 (prescaller /8)
		TIMSK1 |= (1<<ICIE1); //enable input capture interrupts
		sei(); //enable global interupts
	}
	
	float getPeriod() {
		return pulseWidth/(float)(F_CPU/8000);
	}
	
	float getFreq() {
		return 1000/getPeriod();
	}
}