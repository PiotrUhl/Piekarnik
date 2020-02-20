#include "ssr.h"

namespace ssr {
	//initializes electromagnetic relays
	void init() {
		SSR_PORT |= (1<<SSR_SSR1) | (1<<SSR_SSR2); //write 1 (inactive) to relay pins
		SSR_DDR |= (1<<SSR_SSR1) | (1<<SSR_SSR2); //set relay pins as output
	}
	
	//reads state of given relay
	bool get(nr number) {
		switch (number) {
			case SSR1:
				return (~SSR_PORT & (1<<SSR_SSR1));
			case SSR2:
				return (~SSR_PORT & (1<<SSR_SSR2));
			default:
				return false; //should never happen
		}
	}
	
	//sets state of given relay
	void set(nr number, bool val) {
		switch (number) {
		case SSR1:
			if (val == true)
				SSR_PORT &= ~(1 << SSR_SSR1); //set to active - 0
			else
				SSR_PORT |= (1 << SSR_SSR1); //set to inactive - 1
			break;
		case SSR2:
			if (val == true)
				SSR_PORT &= ~(1 << SSR_SSR2); //set to active - 0
			else
				SSR_PORT |= (1 << SSR_SSR2); //set to inactive - 1
		}
	}
}