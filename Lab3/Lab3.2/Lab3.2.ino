//Write a program to measure the ADC conversion time. Configure pin PB0 to be an output pin.
//Write a one to PB0, then start an ADC conversion and write a 0 to PB0 after the conversion
//is complete. Measure the conversion time using an oscilloscope (or Logic Pirate) (Hint: Do
//not write to the serial port with this program because it can alter your measured
//conversion time).
//1. Include an oscilloscope capture of your PB0 pin for the case of a first conversion.
//2. Include an oscilloscope capture of your PB0 pin for the case of subsequent conversions.
//3. Comment in your report about how closely your measured conversion times match the
//expected conversion times according to the ATmega328P data sheet.
//4. Estimate the fasted rate you could sample an input voltage (your answer should be in
//Hz).

# define DEBUG_OUTPUT_MESSAGE_MAX_LENGTH 80
char message [DEBUG_OUTPUT_MESSAGE_MAX_LENGTH];
volatile uint8_t* addADMUX;
volatile uint8_t* addADCSRA;
volatile uint8_t* addADCH;
volatile uint8_t* addADCL;
volatile uint8_t* addADCSRB;
volatile uint8_t* addDIDR0;

volatile uint8_t* ioPORTB;
volatile uint8_t* ioDDRB;

void setup () {
  Serial.begin(9600);
  ioDDRB = (uint8_t) 0x24;
  ioPORTB = (uint8_t) 0x25;

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
  *ioDDRB = 0xFF;
}

void loop() {
  *ioPORTB |= 0x01;//takes 1.6us for the on and off cycle 14.2 us for the 2nd + conversions
  *addADCSRA |= 0x40; // Set the " ADSC start conversion " bit high
  while (* addADCSRA & 0x40) { } // Wait for ADC to finish (i.e. , " ADSC start conversion " bit low)
  //uint16_t Voltage ; // Create 16 bit value to store high and low bytes
  //Voltage = ( uint16_t ) *addADCL | (( uint16_t ) *addADCH << 8) ; // Fill with high and low bytes
  //Serial.println (Voltage); // Convert to actual voltage and display
  // delay(50);
  *ioPORTB = 0x00;
}
