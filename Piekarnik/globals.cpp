#include "globals.h"

//current mode: false - standby mode; true - running mode
bool mode = false;

//is button pressed
bool buttonPressed[8] = {false};

//set temperature
uint16_t tempSet = 100;

//last recorded temperature
uint16_t lastTemp = 0;

//value of time at which temperature will be measured again
uint32_t nextTempMeasure = 0;

//temperature is beeing changed
bool tempChangingMode = false;

//value of time at which temperature changing mode will be left
uint32_t leaveTempChangingModeAt = 0;

//set time [s]
uint16_t timeSet = 0;

//value of time at which timeSet will be decremented
uint32_t timeSetDecrement = 0;

//is light enabled
bool lightOn = false;

//is motor enabled
bool motorOn = false;

//is heater 1 enabled
bool heater1On = true;
//is heater 2 enabled
bool heater2On = false;

//chosen heater
uint8_t chosenHeater = 1;

//buzzer is playing
bool buzzerPlaying = false;

//value of time at which buzzer will stop playing
uint32_t stopBuzzer = 0;