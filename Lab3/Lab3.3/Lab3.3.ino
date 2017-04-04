void setup () {
  DDRB |= 0x02;
  TCCR1A = 0b10000010; 
  TCCR1B = 0b00011101; 
  OCR1A = 16384; 
  ICR1 = 65535;
}
void loop() {
}
