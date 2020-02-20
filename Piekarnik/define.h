#ifndef DEFINE_H_
#define DEFINE_H_

#define IO_OUT MCP_GPIOA //IO output port
#define IO_IN MCP_GPIOB //IO input port

//all inputs active low
#define IO_START 0 //IO start pin (input)
#define IO_HEATER 1 //IO heater choose pin (input)
#define IO_LIGHT 2 //IO light toggle pin (input)
#define IO_MOTOR 3 //IO motor toggle pin (input)
#define IO_TEMPM 4 //IO temperature - pin (input)
#define IO_TEMPP 5 //IO temperature + pin (input)
#define IO_TIMEM 6 //IO time - pin (input)
#define IO_TIMEP 7 //IO time + pin (input)

//all outputs active high
#define IO_LED_START 0 //IO start LED pin (output)
#define IO_LED_HEAT1 1 //IO heater 1 LED pin (output)
#define IO_LED_HEAT2 2 //IO heater 2 LED pin (output)
#define IO_LED_MOTOR 3 //IO motor LED pin (output)
#define IO_LED_LIGHT 4 //IO light LED pin (output)

#endif /* DEFINE_H_ */