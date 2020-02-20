//MAX7219

#ifndef MAX_H_
#define MAX_H_

#include "spi.h" //spi::transmit(), PORTC, DDRC, DDC0

#define MAX_PORT PORTC //MAX CS PORTx
#define MAX_DDR DDRC //MAX CS DDRx
#define MAX_CS PORTC0 //MAX CS pin

//registers
#define MAX_NO_OP 0x00
#define MAX_DIGIT_0 0x01
#define MAX_DIGIT_1 0x02
#define MAX_DIGIT_2 0x03
#define MAX_DIGIT_3 0x04
#define MAX_DIGIT_4 0x05
#define MAX_DIGIT_5 0x06
#define MAX_DIGIT_6 0x07
#define MAX_DIGIT_7 0x08
#define MAX_DECODE_MODE 0x09
#define MAX_INTENSITY 0X0A
#define MAX_SCAN_LIMIT 0X0B
#define MAX_SHUTDOWN 0X0C
#define MAX_DISPLAY_TEST 0X0F

namespace max {
	//initializes MAX7219; SPI must be initialized first
	void init();
	//enters test mode
	void startTest();
	//leaves test mode
	void endTest();
	//sends data byte to register with given address
	void write(uint8_t addr, uint8_t byte = 0xFF);
	
	//writes number to display 1
	void writeNumber1(uint16_t number, uint8_t dots = 0);
	//writes number to display 2
	void writeNumber2(uint16_t number, uint8_t dots = 0);
	//writes Lo to display 1
	void writeLow1();
	//writes Hi to display 1
	void writeHigh1();
	
	
	//clears display 1
	void clear1();
	//clears display 2
	void clear2();
}

#endif /* MAX_H_ */

	/* MAX7219 test
	spi::init();
	max::init();
	while (true) {
		for (int i = 0; i < 9999; i++) {
			max::writeNumber1(i);
			max::writeNumber2(9999-i);
			_delay_ms(100);
		}
	}*/