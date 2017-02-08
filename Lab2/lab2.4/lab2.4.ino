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
  * ioDDRB = 0x01;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(*ioPINB & 0x03){
    debounce();
    if(*ioPINB & 0x01){
      Serial.write("Bounce")
    }
    else{
      Serial.write("No bounce")
    }
  }
}

void debounce(){
  myHardDelay(3);
}

void myHardDelay(long delayInMs){
  float N = 3.0;
  long long iterations = delayInMs*N;
  long long i = 0;
  while(i < iterations){
    i++;
  }
}
