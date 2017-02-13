uint8_t* ioPORTB;
uint8_t* ioDDRB;
uint8_t* ioPINB;

void myHardDelay(long delayInMs);
void debounce();

void setup() {
  // put your setup code here, to run once:
  ioPORTB = ( uint8_t *)0x25;
  ioDDRB = ( uint8_t *)0x24;
  ioPINB = (uint8_t*)0x23;
  pinMode(13,OUTPUT);
  *ioDDRB &= 0xfd;
  *ioPORTB |= 0x02;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if((*ioPINB & 0x02) == 0){
    digitalWrite(13,HIGH);
    //Serial.write("No press\n");
  }
  else{
    digitalWrite(13,HIGH);
  }
  
}

void debounce(){
  myHardDelay(3);
}

void myHardDelay(long delayInMs) {
  float N = 198.43;
  long long iterations = delayInMs * N;
  volatile long long i = 0;
  while (i < iterations) {
    i++;
  }
}
