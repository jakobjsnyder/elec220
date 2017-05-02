#include "ledArray.h"
#include<avr/io.h>
uint8_t frameBufferL = 0xFF;
uint8_t frameBufferH = 0xFF;

void outputToSS(uint8_t* location,uint8_t value){
  if (value == 0){
    *location = 0b01111110;
  } else if (value == 1){
    *location = 0b00010010;
  } else if (value == 2){
    *location = 0b10111100;
  } else if (value == 3){
    *location = 0b10110110;
  } else if (value == 4){
    *location = 0b11010010;
  } else if (value == 5){
    *location = 0b11100110;
  } else if (value == 6){
    *location = 0b11101110;
  } else if (value == 7){
    *location = 0b00110010;
  } else if (value == 8){
    *location = 0b11111110;
  } else if (value == 9){
    *location = 0b11110110;
  }
}

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
void ledArray_flush() {
  //write your code here to send the frameBuffer to the shift register (s)
  PORTB &= 0b11111011 ; // Set SS line low ( tell slave to listen )
  frameBufferL = 0b10111100;
  frameBufferH = 0b00010010;
  outputToSS(&frameBufferL,5);
    outputToSS(&frameBufferH,5);

  SPDR = frameBufferL;
  while (!( SPSR & 0b10000000 ) ) {}
  SPDR = frameBufferH;
  while (!( SPSR & 0b10000000 ) ) {} // Wait for SPI to finish sending byte
  PORTB |= 0b00000100; // Set SS line high ( tell slave to disengage
}


