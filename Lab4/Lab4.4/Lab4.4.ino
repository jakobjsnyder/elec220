#include "ledArray.h"
#include <avr/io.h>
uint8_t frameBufferL = 0xFF;
uint8_t frameBufferH = 0xFF;
uint16_t adcValue = 
void ledArray_init () {
  // write your code here to initialize the SPI peripheral
  DDRB |= 0b00101100 ; // Set SCLK ( ['), MOSI ( PB3), and Slave Select (PB2) high
  SPCR = 0b01010011 ; // SPI enbale , MSB first , master , clock idle low ,
  // detect on rising edge , 125 kHz SPI clock rate
  SPSR = 0b00000000 ; // No interrupt , no double speed CLK
  // clear the display to start off fresh
  ledArray_clear () ; // clear frame buffer
  ledArray_flush () ; // flush to the registers
}
void ledArray_setPin ( uint8_t pin , bool state ) {
  uint16_t fullBuffer;
  // write your code here to manipulate the frameBuffer
  if (state) {
    fullBuffer = 0x01 << pin;
    fullBuffer = fullBuffer ^ 0xFFFF;
    frameBufferL &=  (uint8_t)(fullBuffer & 0x00FF);
    frameBufferH &=  (uint8_t)((fullBuffer & 0xFF00) >> 8);
  }
  else {
    if (pin < 8) {
      pin = 0x01 << pin;
      frameBufferL |= pin;
    }
    else {
      pin = 0x01 << (pin - 8);
      frameBufferH |= pin;
    }
  }
}
void ledArray_clear () {
  frameBufferL = 0xff ; // reset the frame buffer to all - off
  frameBufferH = 0xff ; // reset the frame buffer to all - off
}
void ledArray_flush () {
  //write your code here to send the frameBuffer to the shift register (s)
  PORTB &= 0b11111011 ; // Set SS line low ( tell slave to listen )
  SPDR = frameBufferL;
  while (!( SPSR & 0b10000000 ) ) {}
  SPDR = frameBufferH;
  while (!( SPSR & 0b10000000 ) ) {} // Wait for SPI to finish sending byte
  PORTB |= 0b00000100; // Set SS line high ( tell slave to disengage
}
