#include "functions.h"

#include "temp.h"
#include "time.h"
#include "ssr.h"
#include "rl.h"
#include "buz.h"

//tests if any of buttons if pressed, returns this button or NONE
uint8_t testButtons() {
	uint8_t input = mcp::read(IO_IN);
	
	if ((input & (1<<IO_START)) == 0) {
		if (buttonPressed[IO_START] == false) {
			buttonPressed[IO_START] = true;
			return IO_START;
		}
	}
	else
		buttonPressed[IO_START] = false;
	
	if ((input & (1<<IO_HEATER)) == 0) {
		if (buttonPressed[IO_HEATER] == false) {
			buttonPressed[IO_HEATER] = true;
			return IO_HEATER;
		}
	}
	else
		buttonPressed[IO_HEATER] = false;
	
	if ((input & (1<<IO_LIGHT)) == 0) {
		if (buttonPressed[IO_LIGHT] == false) {
			buttonPressed[IO_LIGHT] = true;
			return IO_LIGHT;
		}
	}
	else
		buttonPressed[IO_LIGHT] = false;
	
	if ((input & (1<<IO_MOTOR)) == 0) {
		if (buttonPressed[IO_MOTOR] == false) {
			buttonPressed[IO_MOTOR] = true;
			return IO_MOTOR;
		}
	}
	else
		buttonPressed[IO_MOTOR] = false;
	
	if ((input & (1<<IO_TEMPM)) == 0) {
		if (buttonPressed[IO_TEMPM] == false) {
			buttonPressed[IO_TEMPM] = true;
			return IO_TEMPM;
		}
	}
	else
		buttonPressed[IO_TEMPM] = false;
	
	if ((input & (1<<IO_TEMPP)) == 0) {
		if (buttonPressed[IO_TEMPP] == false) {
			buttonPressed[IO_TEMPP] = true;
			return IO_TEMPP;
		}
	}
	else
		buttonPressed[IO_TEMPP] = false;
	
	if ((input & (1<<IO_TIMEM)) == 0) {
		if (buttonPressed[IO_TIMEM] == false) {
			buttonPressed[IO_TIMEM] = true;
			return IO_TIMEM;
			}
		}
	else
		buttonPressed[IO_TIMEM] = false;
		
	if ((input & (1<<IO_TIMEP)) == 0) {
		if (buttonPressed[IO_TIMEP] == false) {
			buttonPressed[IO_TIMEP] = true;
			return IO_TIMEP;
		}
	}
	else
		buttonPressed[IO_TIMEP] = false;
		
	return 255;
}

//reads, translates and prints temperature to display 2
void printTemp() {
	if (time::get_ms() >= nextTempMeasure) {
		lastTemp = temp::get();
		nextTempMeasure = time::get_ms() + 1000;
	}
	if (lastTemp < 40)
		max::writeLow1();
	else if (lastTemp > 300)
		max::writeHigh1();
	else {
		max::writeNumber1(lastTemp);
	}
}

//prints current set temperature
void printSetTemp() {
	max::writeNumber1(tempSet, 1);
}

//prints current set time
void printSetTime() {
	max::writeNumber2(timeSet);
}

//buttons pressed
void onHeaterButton() {
	stopBuzzer = time::get_ms() + 40;
	buzzerPlaying = true;
	buz::play();
	if (chosenHeater < 3)
		chosenHeater++;
	else
		chosenHeater = 1;
	actualiseChosenHeater();
}
void onMotorButton() {
	stopBuzzer = time::get_ms() + 40;
	buzzerPlaying = true;
	buz::play();
	if (motorOn == true) {
		motorOn = false;
		mcp::write(IO_OUT, mcp::read(IO_OUT) & ~(1<<IO_LED_MOTOR));
	}
	else {
		motorOn = true;
		mcp::write(IO_OUT, mcp::read(IO_OUT) | (1<<IO_LED_MOTOR));
	}
}
void onLightButton() {
	stopBuzzer = time::get_ms() + 40;
	buzzerPlaying = true;
	buz::play();
	if (lightOn == true) {
		lightOn = false;
		mcp::write(IO_OUT, mcp::read(IO_OUT) & ~(1<<IO_LED_LIGHT));
	}
	else {
		lightOn = true;
		mcp::write(IO_OUT, mcp::read(IO_OUT) | (1<<IO_LED_LIGHT));
	}
}
void onTempMinusButton() {
	stopBuzzer = time::get_ms() + 40;
	buzzerPlaying = true;
	buz::play();
	if (tempChangingMode == false)
		tempChangingMode = true;
	else {
		if (tempSet < 60)
			tempSet = 50;
		else
			tempSet -= 5;
	}
	leaveTempChangingModeAt = time::get_ms() + 5000;
}
void onTempPlusButton() {
	stopBuzzer = time::get_ms() + 40;
	buzzerPlaying = true;
	buz::play();
	if (tempChangingMode == false)
		tempChangingMode = true;
	else {
		if (tempSet > 240)
			tempSet = 250;
		else
			tempSet += 5;
	}
	leaveTempChangingModeAt = time::get_ms() + 5000;
}
void onTimeMinusButton() {
	stopBuzzer = time::get_ms() + 40;
	buzzerPlaying = true;
	buz::play();
	if (timeSet < 10)
		timeSet = 0;
	else
		timeSet -= 5;
}
void onTimePlusButton() {
	stopBuzzer = time::get_ms() + 40;
	buzzerPlaying = true;
	buz::play();
	if (timeSet > 350)
		timeSet = 360;
	else
		timeSet += 5;
}
void onStartButton() {
	stopBuzzer = time::get_ms() + 40;
	buzzerPlaying = true;
	buz::play();
	if (mode == false)
		start();
	else
		stop();
}

//enters running mode
void start() {
	if (timeSet	> 0) {
		mode = true;
		mcp::write(IO_OUT, mcp::read(IO_OUT) | (1<<IO_LED_START));
		timeSetDecrement = time::get_ms() + 60000;
	}
}
//leaves running mode
void stop() {
	mode = false;
	mcp::write(IO_OUT, mcp::read(IO_OUT) & ~(1<<IO_LED_START));
	ssr::set(ssr::SSR1, false); //heater 1
	ssr::set(ssr::SSR2, false); //heater 2
	rl::set(rl::RL1, false); //motor
}
//sets heatexOn variables accordingly to chosenHeater variable
void actualiseChosenHeater() {
	if (chosenHeater == 0) {
		heater1On = false;
		heater2On = false;
		mcp::write(IO_OUT, mcp::read(IO_OUT) & ~(1<<IO_LED_HEAT1) & ~(1<<IO_LED_HEAT2));
	}
	else if (chosenHeater == 1) {
		heater1On = true;
		heater2On = false;
		mcp::write(IO_OUT, (mcp::read(IO_OUT) | (1<<IO_LED_HEAT1)) & ~(1<<IO_LED_HEAT2));
	}
	else if (chosenHeater == 2) {
		heater1On = false;
		heater2On = true;
		mcp::write(IO_OUT, (mcp::read(IO_OUT) & ~(1<<IO_LED_HEAT1)) | (1<<IO_LED_HEAT2));
	}
	else if (chosenHeater == 3) {
		heater1On = true;
		heater2On = true;
		mcp::write(IO_OUT, mcp::read(IO_OUT) | (1<<IO_LED_HEAT1) | (1<<IO_LED_HEAT2));
	}
}

//play ending sound
void playEndingSound() {
	stopBuzzer = time::get_ms() + 1000;
	buzzerPlaying = true;
	buz::play();
}