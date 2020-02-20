//SPI
#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h> //uint8_t, PORTB5, PORTB3, PORTB2, 

//communication pins
#define SPI_SCK PORTB5
#define SPI_MISO PORTB4
#define SPI_MOSI PORTB3
#define SPI_SS PORTB2

namespace spi {
	//initialize SPI
	void init();
	//send byte on SPI and return received byte
	uint8_t transmit(uint8_t byte = 0xFF);
}

#endif /* SPI_H_ */