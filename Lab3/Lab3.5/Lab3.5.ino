//You will be writing an analog input/output program that allows you to control the brightness
//of a single LED with a single input. First, write a program that reads the analog voltage
//drop across a potentiometer. This value should range from 0 to 1023 as the potentiometer is
//adjusted. Next, use this input value to adjust the brightness of an LED from off (0) to full-on
//(1023). In order to do this, you will need to set up the microcontroller to drive the LED using
//a PWM signal (use one of the 8-bit timers on PORTD).
//The resulting demonstration should be such that the LED smoothly transitions from off to
//full-on as the dial is increased from 0 to 1023.


# define DEBUG_OUTPUT_MESSAGE_MAX_LENGTH 80
char message [DEBUG_OUTPUT_MESSAGE_MAX_LENGTH];
volatile uint8_t* addADMUX;
volatile uint8_t* addADCSRA;
volatile uint8_t* addADCH;
volatile uint8_t* addADCL;
volatile uint8_t* addADCSRB;
volatile uint8_t* addDIDR0;

volatile uint8_t* RED;
volatile uint8_t* GREEN;
volatile uint8_t* BLUE;

void setup () {
  Serial.begin(9600);
  addADMUX = (uint8_t *) 0x7C; // Used for ref voltage , left / right justify , & input selection
  addADCSRA = (uint8_t *) 0x7A; // Enable , start ADC , set interrupts , and set prescaling
  addADCH = (uint8_t *) 0x79; // High byte of ADC result
  addADCL = (uint8_t *) 0x78; // Low byte of ADC result
  addADCSRB = (uint8_t *) 0x7B; // Choose source to trigger the start of ADC
  addDIDR0 = (uint8_t *) 0x7E; // Turn off PIN input for each ADC pin ( saves power )
  *addADMUX = 0x45; // Choose Vcc as reference volatage , right justify , and use ADC5
  *addADCSRA = 0x84; // Enable ADC and select prescaling of 16
  *addADCSRB = 0x00; // Disable triggers and set to free - running mode
  *addDIDR0 = 0x3F; // Turn off all PIN inputs

  DDRD |= 0x68; // red = pin 3, green = pin 5, blue = pin 6

  TCCR0A = 0b10100011;//turn on both channels fast pwm
  TCCR0B = 0b00000010;//1/8 multiplier
  TCCR2A = 0b00100011;//turn on channel B fast pwm
  TCCR2B = 0b00000010;//1/8 multiplier
}

void loop() {
  uint8_t aLow, aHigh;
  *addADCSRA |= 0x40; // Set the " ADSC start conversion " bit high
  while (* addADCSRA & 0x40) { } // Wait for ADC to finish (i.e. , " ADSC start conversion " bit low)
  aLow = *addADCL;
  aHigh = *addADCH;
  uint16_t Voltage ; // Create 16 bit value to store high and low bytes
  Voltage = ( uint16_t ) aLow | (( uint16_t ) aHigh << 8) ; // Fill with high and low bytes
  //Serial.println (Voltage); // Convert to actual voltage and display

  uint16_t H = (uint16_t)((double)Voltage / 1023.0 * 360.0);
  //Serial.println(&OCR2B);

  uint8_t X = 255 * (1 - fabs((H % 120) / 60.0 - 1));
//  Serial.println(X);
  //  RED = OCR2B;
  //  BLUE = OCR0B;
  //  GREEN = OCR0A;
  if (H >= 0 && H < 60) {
//    Serial.println("RED");
    OCR2B = 0;
    OCR0B = 255 - X;
    OCR0A = 255;
  }
  else if (H >= 60 && H < 120) {
//    Serial.println("yellow");
    OCR2B = 255 - X;
    OCR0B = 0;
    OCR0A = 255;
  }
  else if (H >= 120 && H < 180) {
//    Serial.println("green");
    OCR2B = 255;
    OCR0B = 0;
    OCR0A = 255 - X;
  }
  else if (H >= 180 && H < 240) {
//    Serial.println("cyan");
    OCR2B = 255;
    OCR0B = 255 - X;
    OCR0A = 0;
  }
  else if (H >= 240 && H < 300) {
//    Serial.println("blue");
    OCR2B = 255 - X;
    OCR0B = 255;
    OCR0A = 0;
  }
  else if (H >= 300 && H <= 360) {
    //Serial.println("magenta");
    OCR2B = 0;
    OCR0B = 255;
    OCR0A = 255 - X;
  }
}
