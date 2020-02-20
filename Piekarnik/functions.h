//functions used by both modes

#ifndef functions_H_
#define functions_H_

#include <avr/io.h>
#include "define.h"
#include "globals.h"
#include "mcp.h"
#include "max.h"
#include "fc.h"

//tests if any of buttons if pressed, returns this buttons pin or 255
uint8_t testButtons();

//reads, translates and prints temperature to display 2
void printTemp();

//prints current set temperature
void printSetTemp();

//prints current set time
void printSetTime();

//buttons pressed
void onHeaterButton();
void onMotorButton();
void onLightButton();
void onTempMinusButton();
void onTempPlusButton();
void onTimeMinusButton();
void onTimePlusButton();
void onStartButton();

//enters running mode
void start();
//leaves running mode
void stop();

//sets heatexOn variables accordingly to chosenHeater variable
void actualiseChosenHeater();

//play ending sound
void playEndingSound();

#endif /* functions_H_ */