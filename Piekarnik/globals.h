//global variables

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <avr/io.h>

//current mode: false - standby mode; true - running mode
extern bool mode;

//is button pressed
extern bool buttonPressed[8];

//set temperature
extern uint16_t tempSet;

//last recorded temperature
extern uint16_t lastTemp;

//value of time at which temperature will be measured again
extern uint32_t nextTempMeasure; 

//temperature is beeing changed
extern bool tempChangingMode;

//value of time at which temperature changing mode will be left
extern uint32_t leaveTempChangingModeAt;

//set time [s]
extern uint16_t timeSet;

//value of time at which timeSet will be decremented
extern uint32_t timeSetDecrement;

//is light enabled
extern bool lightOn;

//is motor enabled
extern bool motorOn;

//is heater 1 enabled
extern bool heater1On;
//is heater 2 enabled
extern bool heater2On;

//chosen heater
extern uint8_t chosenHeater;

//buzzer is playing
extern bool buzzerPlaying;

//value of time at which buzzer will stop playing
extern uint32_t stopBuzzer;

#endif /* GLOBALS_H_ */