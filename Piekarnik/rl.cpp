#include "rl.h"

namespace rl {
	//initializes electromagnetic relays
	void init() {
		RL_PORT &= ~(1<<RL_RL1) & ~(1<<RL_RL2); //write 0 (inactive) to relay pins
		RL_DDR |= (1<<RL_RL1) | (1<<RL_RL2); //set relay pins as output
	}
	
	//reads state of given relay
	bool get(nr number) {
		switch (number) {
		case RL1:
			return (~RL_PORT & (1<<RL_RL1));
		case RL2:
			return (~RL_PORT & (1<<RL_RL2));
		default:
			return false; //should never happen
		}
	}
	
	//sets state of given relay
	void set(nr number, bool val) {
		switch (number) {
		case RL1:
			if (val == true)
				RL_PORT |= (1 << RL_RL1); //set to active - 1
			else
				RL_PORT &= ~(1 << RL_RL1); //set to inactive - 0
			break;
		case RL2:
			if (val == true)
				RL_PORT |= (1 << RL_RL2); //set to active - 1
			else
				RL_PORT &= ~(1 << RL_RL2); //set to inactive - 0
		}
	}
}