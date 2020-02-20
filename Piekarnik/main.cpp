/*
 * Piekarnik.cpp
 *
 * Author : Piotr Uhl
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "define.h" //various defines
#include "mainLoop.h" //standby mode

#include "spi.h" //SPI interface
#include "mcp.h" //IO expander MCP23S17
#include "max.h" //display driver MAX7219
#include "fc.h" //frequency meter
#include "time.h" //timer
#include "rl.h" //electromagnetic relays
#include "ssr.h" //solid state relays
#include "buz.h" //buzzer
#include "temp.h" //temperature

//ports and peripherals initialization
inline void init();
//tests if ODPOST procedure should be run
inline bool testODPOST();
//On Demand Power On Self test
inline void ODPOST();
//working mode
void workingMode();

int main(void) {
	
	init(); //initialization
	if (testODPOST() == true) //test if ODPOST procedure should be run
		ODPOST(); //run ODPOST procedure
	mcp::write(IO_OUT, 0b00000010);
	time::reset();
	time::start();
	mainLoop(); //enters standby mode //debug
}

//ports and peripherals initialization
void init() {
		//initialize ports (all including unused) as input with pull-up
		DDRB = 0x00;
		PORTB = 0xFF;
		DDRC = 0x00;
		PORTC = 0xFF;
		DDRD = 0x00;
		PORTD = 0xFF;
		
		rl::init(); //relays initialization
		ssr::init(); //SSRs initialization
		spi::init(); //SPI initialization
		mcp::init(); //IO expander initialization
		max::init(); //display driver initialization
		fc::init(); //frequency measure initialization
		time::init(); //time measure initialization
		buz::init(); //buzzer initialization
}

//tests if ODPOST procedure should be run
bool testODPOST() {
	uint8_t input = mcp::read(IO_IN);
	if ((input & (1<<IO_LIGHT)) == 0)
		return true;
	else
		return false;
}

//On Demand Power On Self test
void ODPOST() {
	//first test - LEDs, buzzer and general display
	mcp::write(IO_OUT, 0xFF); //turn on all LEDs
	max::startTest(); //enter MAX test mode
	buz::play(); //play sound
	time::start(); //starts timer
	time::reset(); //just for sure
	while (time::get_ms() < 1000); //wait one second
	buz::stop(); //stop sound
	mcp::write(IO_OUT, 0x00); //turn off all LEDs
	max::endTest(); //leave MAX test mode
	time::reset(); //reset timer
	while (time::get_ms() < 1000); //wait one second
	
	//second test - SSR1, relay1 and frequency measurement
	mcp::write(IO_OUT, 0xFF); //turn on all LEDs
	ssr::set(ssr::SSR1, true); //turn on SSR 1
	rl::set(rl::RL1, true); //turn on realy 1
	buz::play(); //play sound
	time::reset(); //reset timer
	while (time::get_ms() < 1000) {
		max::writeNumber1(1234); //writes number to display 1
		max::writeNumber2(5678); //writes number to display 2
	} //wait one second
	buz::stop(); //stop sound
	max::clear1(); //clear displays
	max::clear2();
	mcp::write(IO_OUT, 0x00); //turn off all LEDs
	ssr::set(ssr::SSR1, false); //turn off SSR 1
	rl::set(rl::RL1, false); //turn off realy 1
	time::reset(); //reset timer
	while (time::get_ms() < 1000); //wait one second
	
	//third test - SSR2, relay2 and temperature measurement
	mcp::write(IO_OUT, 0xFF); //turn on all LEDs
	ssr::set(ssr::SSR2, true); //turn on SSR 2
	rl::set(rl::RL2, true); //turn on realy 2
	buz::play(); //play sound
	time::reset(); //reset timer
	while (time::get_ms() < 1000) {
		max::writeNumber1(temp::get()); //writes temperature to display 1
		max::writeNumber2(fc::getFreq()); //writes current time to display 2
	} //wait one second
	buz::stop(); //stop sound
	max::clear1(); //clear displays
	max::clear2();
	mcp::write(IO_OUT, 0x00); //turn off all LEDs
	ssr::set(ssr::SSR2, false); //turn off SSR 2
	rl::set(rl::RL2, false); //turn off realy 2
	time::reset(); //reset timer
	while (time::get_ms() < 1000); //wait one second
	time::reset(); //reset timer
}

	/*
	// Real-time timer rest
	uint32_t lastTime = 0;
	DDRB |= (1<<PORTB1); //PB1 as output
	//PORTB &= ~(1<<PORTB1); //PB5 low
	time::init();
	time::start();
	while (true) {
		PORTB |= (1<<PORTB1); //PB1 high
		while (time::get_s() == lastTime);
		lastTime = time::get_s();
		PORTB &= ~(1<<PORTB1); //PB1 low
		while (time::get_s() == lastTime);
		lastTime = time::get_s();
	}*/
	/*DDRB |= (1<<PORTB1); //PB1 as output
	while(1) {
		PORTB |= (1<<PORTB1);
		_delay_ms(100);
		PORTB &= ~(1<<PORTB1);
		_delay_ms(100);
	}*/