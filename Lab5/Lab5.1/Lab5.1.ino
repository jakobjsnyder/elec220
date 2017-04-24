# include "smbus.h"

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

void setup() {
  // put your setup code here, to run once:
  SMBUS_init();
  SMBUS_writeRegister(MPUADDR, PWR_MGMT_1, 0);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  initializeAcc();
  digitalWrite(13,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t tempAccX = (SMBUS_readRegister(MPUADDR, AccXAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccXAddrL);
  int16_t tempAccY = (SMBUS_readRegister(MPUADDR, AccYAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccYAddrL);
  int16_t tempAccZ = (SMBUS_readRegister(MPUADDR, AccZAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccZAddrL);

  AccX = initialX - tempAccX;
  AccY = initialY - tempAccY;
  AccZ = initialZ - tempAccZ;
  
  Serial.print("\nAccX = "); Serial.print(AccX);
  Serial.print("\tAccY = "); Serial.print(map(AccY,-16384,16384,-90,90));
  Serial.print("\tAccZ = "); Serial.print(map(AccZ,-16384,16384,-90,90));
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

