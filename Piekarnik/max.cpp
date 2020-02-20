#include "max.h"

namespace max {
	
	//initializes MAX7219; SPI must be initialized first
	void init() {
		MAX_DDR |= (1<<MAX_CS); //set CS as output
		MAX_PORT |= (1<<MAX_CS); //set CS bit
		write(MAX_DECODE_MODE, 0b11111111); //decode all digits
		write(MAX_SCAN_LIMIT, 0x07); //scan all 8 digits
		write(MAX_INTENSITY, 0x04); //set max light intensity
		write(MAX_SHUTDOWN, 1); //leave shutdown mode
	}
	
	//enters test mode
	void startTest() {
		write(MAX_DISPLAY_TEST, 0xFF);
	}
	//leaves test mode
	void endTest() {
		write(MAX_DISPLAY_TEST, 0x00);
	}
	
	//sends data byte to register with given address
	void write(uint8_t addr, uint8_t byte) {
		MAX_PORT &= ~(1<<MAX_CS); //clear CS bit
		spi::transmit(addr); //send register address
		spi::transmit(byte); //send data byte
		MAX_PORT |= (1<<MAX_CS); //set CS bit
	}

	//writes number to display 1
	void writeNumber1(uint16_t number, uint8_t dots) {
		bool zeroable = true;
		if (number < 1000)
		write(MAX_DIGIT_4, 0x0F | ((dots & (1<<3))) << 4);
		else {
			write(MAX_DIGIT_4, number/1000 | ((dots & (1<<3))) << 4);
			zeroable = false;
		}
		number %= 1000;
		if (number < 100 && zeroable)
		write(MAX_DIGIT_5, 0x0F | ((dots & (1<<2))) << 5);
		else {
			write(MAX_DIGIT_5, number/100 | ((dots & (1<<2))) << 5);
			zeroable = false;
		}
		number %= 100;
		if (number < 10 && zeroable)
		write(MAX_DIGIT_6, 0x0F | ((dots & (1<<1))) << 6);
		else
		write(MAX_DIGIT_6, number/10 | ((dots & (1<<1))) << 6);
		number %= 10;
		write(MAX_DIGIT_7, number | ((dots & (1<<0))) << 7);
	}
		
	//writes number to display 2
	void writeNumber2(uint16_t number, uint8_t dots) {
		bool zeroable = true;
		if (number < 1000)
			write(MAX_DIGIT_0, 0x0F | ((dots & (1<<3))) << 4);
		else {
			write(MAX_DIGIT_0, number/1000 | ((dots & (1<<3))) << 4);
			zeroable = false;
		}
		number %= 1000;
		if (number < 100 && zeroable)
			write(MAX_DIGIT_1, 0x0F | ((dots & (1<<2))) << 5);
		else {
			write(MAX_DIGIT_1, number/100 | ((dots & (1<<2))) << 5);
			zeroable = false;
		}
		number %= 100;
		if (number < 10 && zeroable)
			write(MAX_DIGIT_2, 0x0F | ((dots & (1<<1))) << 6);
		else
			write(MAX_DIGIT_2, number/10 | ((dots & (1<<1))) << 6);
		number %= 10;
			write(MAX_DIGIT_3, number | ((dots & (1<<0))) << 7);
	}
	
	//writes Lo to display 1
	void writeLow1() {
		write(MAX_DIGIT_4, 0x0F);
		write(MAX_DIGIT_5, 0x0F);
		write(MAX_DIGIT_6, 0x0F);
		write(MAX_DIGIT_7, 13); //L
	}
	//writes Hi to display 2
	void writeHigh1() {
		write(MAX_DIGIT_4, 0x0F);
		write(MAX_DIGIT_5, 0x0F);
		write(MAX_DIGIT_6, 0x0F);
		write(MAX_DIGIT_7, 12); //H
	}
	
	//clears display 1
	void clear1() {
		write(MAX_DIGIT_4, 0x0F);
		write(MAX_DIGIT_5, 0x0F);
		write(MAX_DIGIT_6, 0x0F);
		write(MAX_DIGIT_7, 0x0F);
	}
	//clears display 2
	void clear2() {
		write(MAX_DIGIT_0, 0x0F);
		write(MAX_DIGIT_1, 0x0F);
		write(MAX_DIGIT_2, 0x0F);
		write(MAX_DIGIT_3, 0x0F);
	}
}