//real-time timer
#ifndef TIME_H_
#define TIME_H_

#include <avr/io.h>

namespace time {
	//miliseconds since start
	extern uint32_t milis;
	
	//initializes timer0 for counting seconds
	void init();
	//starts time counter
	void start();
	//pauses time counter
	void pause();
	//resets time counter
	void reset();
	//gets miliseconds count
	uint32_t get_ms();
	//gets seconds count
	uint32_t get_s();
	//gets minutes count
	uint32_t get_min();
	
}

#endif /* TIME_H_ */

	/* Real-time timer test
	uint32_t lastTime = 0;
	DDRB |= (1<<PORTB5); //PB5 as output
	PORTB &= ~(1<<PORTB5); //PB5 low
	time::init();
	time::start();
	while (true) {
		PORTB &= ~(1<<PORTB5); //PB5 low
		while (time::get_s() == lastTime);
		lastTime = time::get_s();
		PORTB |= (1<<PORTB5); //PB5 high
		while (time::get_s() == lastTime);
		lastTime = time::get_s();
	} */