# include "ledArray.h"

void setup () {
  ledArray_init();
}
void loop () {
  for (int i = 0; i < 8; i ++) {
    ledArray_clear () ;
    ledArray_setPin (i , true ) ;
    ledArray_flush () ;
    delay (100) ;
  }
}


//uint8_t frameBuffer = 0xFF;
//void ledArray_setPin(uint8_t pin, bool state);
//void ledArray_clear();
//
//void setup () {
//  DDRB |= 0b00101100 ; // Set SCLK ( ['), MOSI ( PB3), and Slave Select (PB2) high
//  SPCR = 0b01010011 ; // SPI enbale , MSB first , master , clock idle low ,
//  // detect on rising edge , 125 kHz SPI clock rate
//  SPSR = 0b00000000 ; // No interrupt , no double speed CLK
//}
//
//void loop () {
//  ledArray_clear();
//  ledArray_setPin(5, true);
//  delay(500);
//  ledArray_setPin(1, true);
//  delay(500);
//  ledArray_setPin(1, false);
//  delay(500);
//}
//
//void ledArray_setPin(uint8_t pin, bool state) {
//  if (state) {
//    pin = 0x01 << pin;
//    pin = pin ^ 0xFF;
//    frameBuffer &=  pin;
//  }
//  else {
//    pin = 0x01 << pin;
//    frameBuffer |= pin;
//  }
//
//  PORTB &= 0b11111011 ; // Set SS line low ( tell slave to listen )
//  SPDR = frameBuffer;
//  while (!( SPSR & 0b10000000 ) ) {} // Wait for SPI to finish sending byte
//  PORTB |= 0b00000100; // Set SS line high ( tell slave to disengage
//}
//
//void ledArray_clear() {
//  PORTB &= 0b11111011 ; // Set SS line low ( tell slave to listen )
//  frameBuffer = 255;
//  SPDR = frameBuffer;
//  while (!( SPSR & 0b10000000 ) ) {} // Wait for SPI to finish sending byte
//  PORTB |= 0b00000100; // Set SS line high ( tell slave to disengage
//}

