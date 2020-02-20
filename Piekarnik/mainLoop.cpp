#include "mainLoop.h"

#include "ssr.h"
#include "temp.h"
#include "buz.h"

//main program loop
void mainLoop() {
	while (true) {
		
		//decrement time and end work if needed
		if (mode == true) {
			if (time::get_ms() >= timeSetDecrement) {
				timeSetDecrement = time::get_ms() + 60000;
				timeSet--;
			}
			if (timeSet == 0) {
				stop();
				playEndingSound();
			}
		}
		
		//configures relays accordingly to configuration variables
		rl::set(rl::RL2, lightOn); //light
		if (mode == true) { //if working mode
			rl::set(rl::RL1, motorOn); //motor
			if (temp::get() + 5 < tempSet) { //if too cold
				ssr::set(ssr::SSR1, heater1On); //heater 1
				ssr::set(ssr::SSR2, heater2On); //heater 2
			}
			else if (temp::get() - 5 > tempSet) { //if too hot
				ssr::set(ssr::SSR1, false); //heater 1
				ssr::set(ssr::SSR2, false); //heater 2
			}
		}
		
		//print temperature
		if (tempChangingMode == true) {
			//test if changing temperature is finished
			if (time::get_ms() >= leaveTempChangingModeAt) {
				//user is no longer changing temperature
				tempChangingMode = false;
				printTemp();
			}
			else {
				printSetTemp();
			}
		}
		else {
			printTemp();
		}
		
		//prints time
		printSetTime();
		
		//buzzer
		if (buzzerPlaying) {
			if (time::get_ms() >= stopBuzzer) {
				buz::stop();
				buzzerPlaying = false;
			}
		}
		
		//sprawdzanie przycisków
		uint8_t button = testButtons();
		switch (button) {
		case 255:
			break;
		case IO_START:
			onStartButton();
			break;
		case IO_HEATER:
			onHeaterButton();
			break;
		case IO_MOTOR:
			onMotorButton();
			break;
		case IO_LIGHT:
			onLightButton();
			break;
		case IO_TEMPM:
			onTempMinusButton();
			break;
		case IO_TEMPP:
			onTempPlusButton();
			break;
		case IO_TIMEM:
			onTimeMinusButton();
			break;
		case IO_TIMEP:
			onTimePlusButton();
			break;
		}
	}
}