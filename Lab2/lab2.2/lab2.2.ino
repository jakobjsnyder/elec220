#include "stdint.h";
#include "stdio .h";
// global variables
uint8_t* ioPORTB;
uint8_t* ioDDRB;
char message [80];

void setup() {
  // put your setup code here, to run once:
  ioPORTB = ( uint8_t *) 0x25 ;
  ioDDRB = ( uint8_t *) 0 x24;
  // make PB0 an output
  * ioDDRB = 0x01;
}

void loop() {
  // put your main code here, to run repeatedly:
  // set PB0 high
  * ioPORTB = 0x01;
  sprintf ( message , " Format the message \n") ;
  // set PB0 low
  * ioPORTB = 0x00;
}
