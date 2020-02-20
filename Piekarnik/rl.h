//electromagnetic relays

#ifndef RL_H_
#define RL_H_

#include <avr/io.h>

#define RL_PORT PORTC //relays PORTx
#define RL_DDR DDRC //relays DDRx
#define RL_RL1 PORTC4 //relay 1 pin //active high!
#define RL_RL2 PORTC5 //relay 2 pin //active high!

namespace rl {
	
	enum nr : char {
		RL1 = 1,
		RL2
	};
	
	//initializes electromagnetic relays
	void init();
	//reads state of given relay
	bool get(nr); 
	//sets state of given relay
	void set(nr, bool);
}

#endif /* RL_H_ */