
uint8_t* ioPORTB;
uint8_t* ioDDRB;

void setup() {
  // put your setup code here, to run once:
  ioPORTB = ( uint8_t *)0x25;
  ioDDRB = ( uint8_t *)0x24;
  * ioDDRB = 0x01;
}

void loop() {
  // put your main code here, to run repeatedly:
  // set PB0 high
  * ioPORTB = 0x01;
  // set PB0 low
  * ioPORTB = 0x00;
}
