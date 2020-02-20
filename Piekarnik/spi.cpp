#include "spi.h"

namespace spi {
	
	void init() {
		DDRB |= (1<<SPI_SCK) | (1<<SPI_MOSI) | (1<<SPI_SS); //set SCK, MOSI and SS as outputs
		PORTB |= (1<<SPI_SS); //just for sure
		DDRB &= ~(1<<SPI_MISO); //set MISO as input
		PORTB &= ~(1<<SPI_MISO); //disable MISO pullup resistor
		SPCR = 0x00; //zero control register (trying to fix a bug)
		SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR1) | (1<<SPR0); //enable SPI, set as Master, clk fosc/128
		//SPCR = (1<<SPE) | (1<<MSTR); //enable SPI, set as Master, clk fosc/2
		//SPSR |= (1 << SPI2X); //clk fosc/2
	}
	
	uint8_t transmit(uint8_t byte) {
		SPDR = byte; //send byte
		while(!(SPSR & (1<<SPIF))) //wait until transmission completed
			;
		return SPDR; //return received byte
	}
	
}