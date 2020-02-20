#include "temp.h"

namespace temp {
	
	//gets current temperature in Celsius degrees
	uint16_t get() {
		//return fc::getFreq() * -1.810706555 + 731.6936972;
		return fc::getFreq() * -1.810706555 + 688; //kalibracja na oko
	}
	
}