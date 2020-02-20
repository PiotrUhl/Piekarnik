//frequency counter
#ifndef FC_H_
#define FC_H_

#include <avr/io.h>

namespace fc {
	//last captured timer value
	extern uint16_t lastCapture;
	//last measured pulse width
	extern uint16_t pulseWidth;
	
	//initializes frequency measurment
	void init();
	//get last measured pulse period [ms]
	float getPeriod();
	//gets last measured frequency [kHz]
	float getFreq();
}

#endif /* FC_H_ */

	/* Frequency read rest
	fc::init();
	while (true) {
		fc::getFreq();
		_delay_ms(500);
	}
	*/