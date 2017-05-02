#include "smbus.h"
#include "ss.h"
#include "tarefreeze.h"

#define DEBUG_OUTPUT_MESSAGE_MAX_LENGTH 80
char message[ DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ];

uint8_t MPUADDR = 0x68;
uint8_t PWR_MGMT_1 = 0x6B;
int16_t AccX, AccY, AccZ;
int32_t initialX, initialY, initialZ;
uint8_t AccXAddrH = 0x3B;
uint8_t AccXAddrL = 0x3C;
uint8_t AccYAddrH = 0x3D;
uint8_t AccYAddrL = 0x3E;
uint8_t AccZAddrH = 0x3F    ;
uint8_t AccZAddrL = 0x40;

uint8_t tarePreviousState = 1;
boolean freezeState = false;
int16_t tareValue = 0;
int16_t freezeValue = 0;
void initializeAcc();

void attachServo() {
  DDRB |= 0x02;
  TCCR1A = 0b10000010;
  TCCR1B = 0b00011100;
  ICR1 = 1250;
}

void setServo(int angle) {
  OCR1A = (uint16_t)map(angle, 0, 180, 43, 170);
}

void setup() {
  // put your setup code here, to run once:
  SMBUS_init();
  // setup seven segment display
  screen_init();

  SMBUS_writeRegister(MPUADDR, PWR_MGMT_1, 0);
  Serial.begin(9600);
  initializeAcc();
  attachServo();
  // setting PD2 and PD3 as an output for LED
  DDRD |= 0b00001100;
  //set PB0 to an input
  DDRB &= 0b11111110;
  PORTB |= 0x01;
  //set PC0 to an input
  DDRC &= 0b11111110;
  PORTC |= 0x01;
  
  tareValue = readEEPROM();
}



void loop() {
  int16_t tempAccY = (SMBUS_readRegister(MPUADDR, AccYAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccYAddrL);

  AccY = initialY - tempAccY;

  int16_t mapping = map(AccY, -16384, 16384, -90, 90);
  uint16_t angle = mapping - tareValue;
  // see if the tare button is pressed.
  if ((PINB & 0x01) == 0 && tarePreviousState == 1) {
    tarePreviousState = 0;
    // checking to see if the button was pressed for more than 1s.
    delay(1000);
    if ((PINB & 0x01) == 0) {
      // setting value to current angle
      tareValue = mapping;
      // write to EEPROM
      writeEEPROM(tareValue);

    }
    // periodically checking to see if the button is still pressed down.
    for (int i = 0; i < 4; i++) {
      delay(500);
      if ((PINB & 0x01) == 0) {
        tareValue = mapping;
        // write to EEPROM
        writeEEPROM(tareValue);
      }
    }
    delay(100);
    // check if button is pressed down after 3 seconds.
    if ((PINB & 0x01) == 0) {
      tareLED();
      tareValue = 0;
      // write to EEPROM
      writeEEPROM(tareValue);
    }
  }
  Serial.print(tareValue);
  Serial.print("\n");
  // change the previous state of the tare button so it knows if the button was recently pressed
  if ((PINB & 0x01) == 1) {
    tarePreviousState = 1;
  }
  // if the freeze button is pushed
  if ((PINC & 0x01) == 0 ) {
    debounce();
    // if freeze is on - turn it off
    if (freezeState == true) {
      freezeState = false;
      // if freeze is off - turn it on
    } else if ( freezeState == false) {
      freezeValue = angle;
      freezeState = true;
    }
  }

  if (freezeState == true) {
    screen_set_value(freezeValue);
    setServo(freezeValue + 90);
  } else {
    screen_set_value(angle);
    setServo(angle + 90);

  }
  delay(100);

}

void initializeAcc() {
  int i = 0;
  for (i = 0; i < 100; i++) {
    initialY += (SMBUS_readRegister(MPUADDR, AccYAddrH) << 8) | SMBUS_readRegister(MPUADDR, AccYAddrL);
  }
  initialY /= 100;

  delay(500);
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

// flash the tare reset LED
void tareLED() {
  PORTD |= 0b00001100;
  delay(200);
  PORTD &= 0b11110111;
  delay(200);
}

void writeEEPROM(int16_t value) {
  EECR &= 0b11001111 ; // Set Erase & Write Mode
  while ( EECR & 0x02) ; // Wait for any current write to finish
  EEARH = 0; // High byte of EEPROM address
  EEARL = 0; // Low byte of EEPROM address
  EEDR = value; // Example value to write to EEPROM
  PORTB |= 0b00100000 ; // Set PB5 high
  EECR |= 0b00000100 ; // Set EEMPE before EEPE
  EECR |= 0b00000010 ; // Set EEPE to write value
  while ( EECR & 0x02) ; // Wait for write to finish
  PORTB &= ~0b00100000 ; // Set PB5 low
}
int16_t readEEPROM() {
  while (EECR & 0x02) ; // Wait for any current read to finish
  EEARH = 0; // High byte of EEPROM address
  EEARL = 0; // Low byte of EEPROM address
  EECR |= 0b00000001 ; // Set EERE to read
  int16_t data = EEDR ; // Fetch data from EEPROM
  return data;
}


