#include "buz.h"

namespace buz {
	
	//initializes buzzer
	void init() {
			BUZ_PORT |= (1<<BUZ_P); //write 1 (inactive) to buzzer pin
			BUZ_DDR |= (1<<BUZ_P); //set relay pins as output
	}
	//reads current state of buzzer
	bool get() {
		return (~BUZ_PORT & (1<<BUZ_P));
	}
	//starts buzzing
	void play() {
		BUZ_PORT &= ~(1<<BUZ_P);
	}
	//stops buzzing
	void stop() {
		BUZ_PORT |= (1<<BUZ_P);
	}
}