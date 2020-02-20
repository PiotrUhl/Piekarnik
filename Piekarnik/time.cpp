#include "time.h"

#include <avr/interrupt.h>

//needs to be rewritten when system clock is changed

namespace time {
	
	uint32_t milis = 0;
		
	ISR(TIMER0_OVF_vect) {
		milis++;
		TCNT0 = 131;
	}
	
	void init() {
		milis = 0; //zero to time counter
		TCCR0A = 0x00;
		TIMSK0 |= (1<<TOIE0); //enable overflow interrupts
		sei(); //enable global interupts
	}

	void start() {
		TCCR0B = 0b00000011; //1CS12, CS11, CS10 = 011 (prescaller /64)
	}

	void pause() {
		TCCR0B = 0x00; //1CS12, CS11, CS10 = 000 (timer stopped)
	}

	void reset() {
		milis = 0;
		TCNT0 = 131;
	}

	uint32_t get_ms() {
		return milis;
	}
	
	uint32_t get_s() {
		return milis/1000;
	}
	
	uint32_t get_min() {
		return milis/60000;	
	}
}