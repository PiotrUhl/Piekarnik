//MCP23S17
#ifndef MCP_H_
#define MCP_H_

#include "spi.h" //spi::transmit(), PORTC, DDRC, DDC1

//chip select pin
#define MCP_PORT PORTC //MCP CS PORTx
#define MCP_DDR DDRC //MCP CS DDRx
#define MCP_CS PORTC1 //MCP CS pin

//registers
#define MCP_IODIRA 0x00
#define MCP_IODIRB 0x01
#define MCP_IPOLA 0x02
#define MCP_IPOLB 0x03
#define MCP_GPINTENA 0x04
#define MCP_GPINTENB 0x05
#define MCP_DEFVALA 0x06
#define MCP_DEFVALB 0x07
#define MCP_INTCONA 0x08
#define MCP_INTCONB 0x09
#define MCP_IOCONA 0x0A
#define MCP_IOCONB 0x0B
#define MCP_GPPUA 0x0C
#define MCP_GPPUB 0x0D
#define MCP_INTFA 0x0E
#define MCP_INTFB 0x0F
#define MCP_INTCAPA 0x10
#define MCP_INTCAPB 0x11
#define MCP_GPIOA 0x12
#define MCP_GPIOB 0x13
#define MCP_OLATA 0x14
#define MCP_OLATB 0x15

namespace mcp {
	//initializes MCP23S17; SPI must be initialized first
	void init();
	//sends data byte to register with given address
	void write(uint8_t addr, uint8_t byte = 0xFF);
	//reads data byte from register with given address
	uint8_t read(uint8_t addr);
}

#endif /* MCP_H_ */