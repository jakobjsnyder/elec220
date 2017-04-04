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

volatile uint8_t* cPORTB;
volatile uint8_t* cDDRB;
volatile uint8_t* cTCCR1A;
volatile uint8_t* cTCCR1B;
volatile uint8_t* cOCR1AH;
volatile uint8_t* cOCR1AL;


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

  cDDRB = (uint8_t *) 0x24;
  cTCCR1A = (uint8_t *) 0x80;
  cTCCR1B = (uint8_t *) 0x81;
  cOCR1AH = (uint8_t *) 0x89;
  cOCR1AL = (uint8_t *) 0x88;

  *cDDRB |= 0x02; // Set OC1 ( PB1) to an output
  *cTCCR1A = 0b10000011 ; // Turn on (non - inverting ) WGM for COMA and set bits 1: 0 of WGM
  *cTCCR1B = 0b00001010 ; // Set bits 3:2 of WGM and set prescaler to 1 / 8
  *cOCR1AH = 0; // Define the output compare value
  *cOCR1AL = 0; // Define the output compare value
}

void loop() {
  uint8_t aLow, aHigh;
  *addADCSRA |= 0x40; // Set the " ADSC start conversion " bit high
  while (* addADCSRA & 0x40) { } // Wait for ADC to finish (i.e. , " ADSC start conversion " bit low)
  aLow = *addADCL;
  aHigh = *addADCH;
  uint16_t Voltage ; // Create 16 bit value to store high and low bytes
  Voltage = ( uint16_t ) aLow | (( uint16_t ) aHigh << 8) ; // Fill with high and low bytes
  Serial.println (Voltage); // Convert to actual voltage and display

  *cOCR1AH = aHigh;
  *cOCR1AL = aLow;
}
