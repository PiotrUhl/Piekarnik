//solid state relays

#ifndef SSR_H_
#define SSR_H_

#include <avr/io.h>

#define SSR_PORT PORTC //SSRs PORTx
#define SSR_DDR DDRC //SSRs DDRx
#define SSR_SSR1 PORTC2 //SSR 1 pin //active low
#define SSR_SSR2 PORTC3 //SSR 2 pin //active low

namespace ssr {
	
	enum nr : char {
		SSR1 = 1,
		SSR2
	};
	
	//initializes solid state relays
	void init();
	//reads state of given relay
	bool get(nr);
	//sets state of given relay
	void set(nr, bool);
}

#endif /* SSR_H_ */