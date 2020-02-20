//buzzer

#ifndef BUZ_H_
#define BUZ_H_

#include <avr/io.h>

#define BUZ_PORT PORTD //buzzer PORTx
#define BUZ_DDR DDRD //buzzer DDRx
#define BUZ_P PORTD7 //buzzer pin //active low

namespace buz {
	
	//initializes buzzer
	void init();
	//reads current state of buzzer
	bool get();
	//starts buzzing
	void play();
	//stops buzzing
	void stop();
}

#endif /* BUZ_H_ */