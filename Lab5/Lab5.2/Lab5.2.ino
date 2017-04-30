# include "smbus.h"
# include <Servo.h>
Servo myservo;
int pos = 0;

uint8_t MPUADDR = 0x68;
uint8_t PWR_MGMT_1 = 0x6B;
int16_t AccX, AccY, AccZ, GyroX, GyroY, GyroZ;
int32_t initialX, initialY, initialZ;
uint8_t AccXAddrH = 0x3B;
uint8_t AccXAddrL = 0x3C;
uint8_t AccYAddrH = 0x3D;
uint8_t AccYAddrL = 0x3E;
uint8_t AccZAddrH = 0x3F;
uint8_t AccZAddrL = 0x40;
uint8_t GyroXAddrH = 0x43;
uint8_t GyroXAddrL = 0x44;
uint8_t GyroYAddrH = 0x45;
uint8_t GyroYAddrL = 0x46;
uint8_t GyroZAddrH = 0x47;
uint8_t GyroZAddrL = 0x48;

void initializeAcc();
void attachServo();
void servoWrite(int angle);
uint16_t getADC();
int convertADCToAngle(uint16_t adcVal);
void setServo(int angle);
void adc_init();

void setup() {
  // put your setup code here, to run once:
  // SMBUS_init();
  //SMBUS_writeRegister(MPUADDR, PWR_MGMT_1, 0);
  Serial.begin(9600);
  //initializeAcc();
  attachServo();
  adc_init();
  setServo(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println("connected");
  //getAndPrintAccData();
  //uint16_t adcVal = getADC();
  //int angle = convertADCToAngle(adcVal);
  Serial.print(TCNT1);
  Serial.print("\t--\t");
  Serial.print(PB1);
  Serial.print("\n");

  //setServo(angle);
  //sweepServo();
}
// TODO change this to real code
void attachServo() {
  //myservo.attach(9);
  DDRB = 0x02;
  TCCR1A = 0b11000011;
  TCCR1B = 0b00010001;
}

uint16_t getADC() {
  ADCSRA |= 0x40; // Set the " ADSC start conversion " bit high
  while (ADCSRA & 0x40) { } // Wait for ADC to finish (i.e. , " ADSC start conversion " bit low)
  return ( uint16_t ) ADCL | (( uint16_t ) ADCH << 8) ; // Fill with high and low bytes
}

int convertADCToAngle(uint16_t adcVal) {
  return map(adcVal, 1023, 0, 0, 180);
}

void setServo(int angle) {
  OCR1A = 30000;
}

void adc_init() {
  ADMUX = 0x45; // Choose Vcc as reference volatage , right justify , and use ADC5
  ADCSRA = 0x84; // Enable ADC and select prescaling of 16
  ADCSRB = 0x00; // Disable triggers and set to free - running mode
}

void sweepServo() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void getAndPrintAccData() {
  int16_t tempAccX = (SMBUS_readRegister(MPUADDR, AccXAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccXAddrL);
  int16_t tempAccY = (SMBUS_readRegister(MPUADDR, AccYAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccYAddrL);
  int16_t tempAccZ = (SMBUS_readRegister(MPUADDR, AccZAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccZAddrL);

  AccX = initialX - tempAccX;
  AccY = initialY - tempAccY;
  AccZ = initialZ - tempAccZ;

  Serial.print("\nAccX = "); Serial.print(AccX);
  Serial.print("\tAccY = "); Serial.print(map(AccY, -16384, 16384, -90, 90));
  Serial.print("\tAccZ = "); Serial.print(map(AccZ, -16384, 16384, -90, 90));
}

void initializeAcc() {
  int i = 0;
  for (i = 0; i < 100; i++) {
    initialX += (SMBUS_readRegister(MPUADDR, AccXAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccXAddrL);
    initialY += (SMBUS_readRegister(MPUADDR, AccYAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccYAddrL);
    initialZ += (SMBUS_readRegister(MPUADDR, AccZAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccZAddrL);
  }
  initialX /= 100;
  initialY /= 100;
  initialZ /= 100;
  Serial.print("\ninitalX = "); Serial.print(initialX);
  Serial.print("\tinitalY = "); Serial.print(initialY);
  Serial.print("\tinitalZ = "); Serial.print(initialZ);
  delay(500);
}

