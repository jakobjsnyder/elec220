//Write a program to measure the analog voltage on the PC0(ADC0) pin using the ADC peripheral
//with VREF selected to be AVCC. Using a voltage source, apply a DC voltage to ADC0 and
//record measurements at 20 different input voltages between 0 and 5 volts. Use a multimeter
//to measure the actual input voltage Vin.
//1. Measure the supply voltage AVCC on the 5V pin.
//2. Provide a table that includes the measured (by multimeter) voltage Vin, the expected
//ADC value for Vin, the recorded ADC value (a 10-bit unsigned integer), and the voltage
//that the ADC value represents.
//3. Do your measurements match your expectations? How do you expect the measurement
//from Part 1 to affect these results? Explain your answer.
//4. Plot the recorded ADC value (y-axis) versus the measured input voltage Vin (x-axis).

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
}

void loop() {
  uint8_t aLow , aHigh ;
  * addADCSRA |= 0x40; // Set the " ADSC start conversion " bit high
  while (* addADCSRA & 0x40) { } // Wait for ADC to finish (i.e. , " ADSC start conversion " bit low)
  aLow = * addADCL ; // Read the low byte
  aHigh = * addADCH ; // Read the high byte
  uint16_t Voltage ; // Create 16 bit value to store high and low bytes
  Voltage = ( uint16_t ) aLow | (( uint16_t ) aHigh << 8) ; // Fill with high and low bytes
  //snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ,
//             "L = %d\nH = %d\n", aLow , aHigh ) ; // Write values of high and low bytes to char array
  //Serial.write ( message ) ; // Write display to serial port
  Serial.println (Voltage); // Convert to actual voltage and display
  //delay (2000) ; // Delay ADC results by 2 seconds
}
