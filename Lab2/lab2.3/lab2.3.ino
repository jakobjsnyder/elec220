

uint8_t* ioPORTB;
uint8_t* ioDDRB;

void myHardDelay(long delayInMs);
void setup() {
  // put your setup code here, to run once:
  ioPORTB = ( uint8_t *)0x25;
  ioDDRB = ( uint8_t *)0x24;
  * ioDDRB = 0x02;
}

void loop() {
  // put your main code here, to run repeatedly:
  // set PB0 high
  * ioPORTB |= 0x02;
  //delay for 1ms
  myHardDelay(35000);
  //delay(5);
  // set PB0 low
  * ioPORTB &= 0xfd;
  //delay(5);
  myHardDelay(35000);
}

void myHardDelay(long delayInMs) {
  float N = 198.43;
  long long iterations = delayInMs * N;
  volatile long long i = 0;
  while (i < iterations) {
    i++;
  }
}

