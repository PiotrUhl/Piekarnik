#include "mcp.h"

#define MCP_SLAVE_WRITE 0x00 //write bit
#define MCP_SLAVE_READ 0x01 //read bit

#define MCP_SLAVE_ID 0b01000000 //device id
#define MCP_SLAVE_ADDR 0x00 //device address

namespace mcp {
	
	void init() {
		MCP_DDR |= (1<<MCP_CS); //set CS as output
		MCP_PORT |= (1<<MCP_CS); //set CS bit
		write(MCP_IOCONA, 0b00100000); //BANK=0, MIRROR=0, SEQOP=1(disabled), DISSLW=0, HAEN=0, ODR=0, INTPOL=0, UNIMPLEMENTED
		write(MCP_IODIRA, 0x00); //set GPIOA as output
		write(MCP_GPIOA, 0x00); //set outputs low
		write(MCP_IODIRB, 0xFF); //set GPIOB as input
		//write(MCP_GPPUB, 0xFF); //enable pull-up resistors on GPIOB
	}
	
	void write(uint8_t addr, uint8_t byte) {
		MCP_PORT &= ~(1<<MCP_CS); //clear CS bit
		spi::transmit(MCP_SLAVE_ID | ((MCP_SLAVE_ADDR << 1) & 0b00001110) | MCP_SLAVE_WRITE); //send opcode
		spi::transmit(addr); //send register address
		spi::transmit(byte); //send data byte
		MCP_PORT |= (1<<MCP_CS); //set CS bit
	}
	
	uint8_t read(uint8_t addr) {
		MCP_PORT &= ~(1<<MCP_CS); //clear CS bit
		spi::transmit(MCP_SLAVE_ID | ((MCP_SLAVE_ADDR << 1) & 0b00001110) | MCP_SLAVE_READ); //send opcode
		spi::transmit(addr); //send register address
		uint8_t ret = spi::transmit(); //send anything, save answer
		MCP_PORT |= (1<<MCP_CS); //set CS bit
		return ret; //return answer
	}
	
}

	/* MCP23S17 test
	spi::init();
	mcp::init();
	mcp::write(MCP_GPIOA, 0x00);
	mcp::write(MCP_GPIOB, 0xFF);

	uint8_t byte = 0b00000001;
	
    while (true) {
		while (mcp::read(MCP_GPIOB) == 0xFF); //wait until button pressed
		mcp::write(MCP_GPIOA, byte);
		byte = byte << 1;
		if (byte == 0x00)
			byte = 0x01;
		_delay_ms(1);
		while (mcp::read(MCP_GPIOB) != 0xFF); //wait until button freed
    }*/