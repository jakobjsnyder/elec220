// global variables
uint8_t* ioPORTB;
uint8_t* ioDDRB;
char message [80];

void setup() {
  // put your setup code here, to run once:
  ioPORTB = ( uint8_t *) 0x25;
  ioDDRB = ( uint8_t *) 0x24;
  // make PB0 an output
  * ioDDRB = 0x02;
}

void loop() {
  // put your main code here, to run repeatedly:
  // set PB0 high
  * ioPORTB |= 0x02;
  sprintf ( message , "Very Long Message  Very Long Message  Very Long Message");
  * ioPORTB &= 0xfd;
}
