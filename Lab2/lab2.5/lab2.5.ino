volatile uint8_t* ioPORTB;
volatile uint8_t* ioDDRB;
volatile uint8_t* ioPINB;

volatile uint8_t* ioPORTC;
volatile uint8_t* ioDDRC;
volatile uint8_t* ioPINC;

volatile uint8_t* ioPORTD;
volatile uint8_t* ioDDRD;

void myHardDelay(long delayInMs);
void debounce();

void setup() {
  // put your setup code here, to run once:
  ioPORTB = ( uint8_t *)0x25;
  ioDDRB = ( uint8_t *)0x24;
  ioPINB = (uint8_t*)0x23;

  ioPORTC = ( uint8_t *)0x28;
  ioDDRC = ( uint8_t *)0x27;
  ioPINC = (uint8_t*)0x26;

  ioPORTD = ( uint8_t *)0x2B;
  ioDDRD = ( uint8_t *)0x2A;

  *ioDDRB &= 0xfe;
  *ioDDRC &= 0xfe;
  *ioDDRD |= 0x60;

  *ioPORTB |= 0x01;
  *ioPORTC |= 0x01;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((*ioPINB & 0x01) == 0 && (*ioPINC & 0x01) == 0) {
    debounce();
    *ioPORTD &= 0x9f;
    *ioPORTD |= 0x60;
    Serial.write("PB0 Pressed and PC0 Pressed\n");
  }
  else if ((*ioPINB & 0x01) == 0 ) {
    debounce();
    *ioPORTD &= 0x9f;
    *ioPORTD |= 0x40;
    Serial.write("PB0 Pressed\n");
  }
  else if ((*ioPINC & 0x01) == 0 ) {
    debounce();
    *ioPORTD &= 0x9f;
    *ioPORTD |= 0x40;
    Serial.write("PC0 Pressed\n");
  } else {
    *ioPORTD &= 0x9f;
  }
}

void debounce() {
  myHardDelay(20);
}

void myHardDelay(long delayInMs) {
  float N = 198.43;
  long long iterations = delayInMs * N;
  volatile long long i = 0;
  while (i < iterations) {
    i++;
  }
}
