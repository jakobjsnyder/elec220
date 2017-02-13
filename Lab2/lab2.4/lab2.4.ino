volatile uint8_t* ioPORTB;
volatile uint8_t* ioDDRB;
volatile uint8_t* ioPINB;

void myHardDelay(long delayInMs);
void debounce();

void setup() {
  // put your setup code here, to run once:
  ioPORTB = ( uint8_t *)0x25;
  ioDDRB = ( uint8_t *)0x24;
  ioPINB = (uint8_t*)0x23;
  pinMode(13, OUTPUT);
  *ioDDRB &= 0xfe;
  *ioPORTB |= 0x01;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if ((*ioPINB & 0x01) == 0) {
    debounce();
    if ((*ioPINB & 0x01) == 0) {
      Serial.print("Bounce\n");
    }
    else {
      Serial.print("No Bounce\n");
    }
  }


}

void debounce() {
  myHardDelay(150);
}

void myHardDelay(long delayInMs) {
  float N = 198.43;
  long long iterations = delayInMs * N;
  volatile long long i = 0;
  while (i < iterations) {
    i++;
  }
}
