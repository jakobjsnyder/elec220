/**
 * MODULE INCLUDES
 * 
 * Specify any includes required by this module
 */
 
#include "smbus.h"
#include "Arduino.h"
#include "Wire.h"

/**
 * Enables the TWI module, sets the correct clock rate, and performs
 * any other initial housekeeping you may need done in this module.
 * 
 * This function should be called by the user (you) before any other SMBUS_ functions.
 */
void SMBUS_init()
{
  TWSR = 0x00;
  TWBR = 0x0C;
  TWCR = 1<<TWEN;
}

/**
 * PRIVATE METHOD PROTOTYPES
 * 
 * Declare any private methods here that you don't want the outside world to
 * be able to call. By convention, private (internal) methods aren't prefaced with
 * the module name.
 * 
 */
 void start();
 void stop();
 void write(uint8_t data);
 uint8_t read(uint8_t shouldAck);


/**
 * MODULE METHOD IMPLEMENTATIONS
 * Put your implementations for this module's methods here
 * 
 * HINTS:
 * SMBus specifies 7-bit addresses (0-127). The read/write bit 
 * that's part of the address byte sent on the bus is *not* considered
 * to be part of the device's address.
 * 
 * For example, to write to a device with address 0x20, you place 0x40 
 * on the bus; to read from 0x20, you place 0x41 on the bus. 
 * 
 * Make sure to take this into consideration when implementing
 * these functions, as you may have to shift the address around a bit.
 * 
 * Standard SMBus terminology:
 * S: Start
 * P: Stop
 * Wr: Write enabled (R/W bit = 0)
 * A: Ack
 * NA: Nack
 * []: Anything sent by the device
 */


/**
 * Read from a register from the SMBus device
 * 
 * devAddr: the 7-bit address specifying the device to read from.
 * regAddr: the address of the device's register to read.
 * 
 * Hint: the format of this transaction is: 
 * S devAddr Wr [A] regAddr [A] S devAddr Rd [A] [Data] NA P
 */
uint8_t SMBUS_readRegister(uint8_t devAddr, uint8_t regAddr)
{
  start();                    // S
  write(devAddr << 1);        // devAddr Wr [A]
  write(regAddr);             // regAddr    [A}
  
  start();                    // S
  write(devAddr << 1 | 0x01); // devAddr Rd [A]
  uint8_t val = read(0);      // [Data] NA
  stop();                     // P
  return val;
}

/**
 * Read a 16-bit word from the SMBus device
 * 
 * devAddr: the 7-bit address specifying the device to read from.
 * regAddr: the address of the device's register to read.
 * 
 * Hint: the format of this transaction is: 
 * S devAddr Wr [A] regAddr [A] S devAddr Rd [A] [HiByte] A [LoByte] NA P
 */
uint16_t SMBUS_readRegisterWord(uint8_t devAddr, uint8_t regAddr)
{
  // implement this function if you want to use it!
}

/**
 * Read a block of data from the SMBus device
 * 
 * devAddr: the 7-bit address specifying the device to read from.
 * regAddr: the address of the device's register to start reading from
 * buffer: the buffer to read the data into
 * Hint: the format of this transaction is: 
 * S devAddr Wr [A] regAddr [A] S devAddr Rd [A] ([Data] A, ...) [Data] NA P
 */
void SMBUS_readRegister(uint8_t devAddr, uint8_t regAddr, uint8_t* buffer, size_t numBytesToRead)
{
  // implement this function if you want to use it!
}

/**
 * Write to an SMBus device's register.
 * 
 * devAddr: the 7-bit address specifying the device to write to.
 * regAddr: the address of the device's register to write.
 * regVal: the value to write to the register.
 * 
 * Hint: the format of this transaction is:
 * format: S devAddr Wr [A] regAddr [A] regVal [A] P
 */
uint8_t SMBUS_writeRegister(uint8_t devAddr, uint8_t regAddr, uint8_t regVal)
{
  start();                  // S
  write(devAddr << 1);      // devAddr Wr [A]
  write(regAddr);           // regAddr    [A]
  write(regVal);            // regVal     [A]
  stop();                   // P
}

/**
 * Low-level I2C functions.
 * 
 * Implement your TWI register-level code in these functions
 */
 
/**
 * Start an i2C transaction.
 */
void start()
{
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while ((TWCR & (1<<TWINT)) == 0);
}

/**
 * Stop an i2C transaction.
 */
void stop()
{
  TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

/**
 * Write a byte to the bus.
 * 
 * data: the byte to write.
 */
void write(uint8_t data)
{
  TWDR = data;
  TWCR = (1<<TWINT)|(1<<TWEN);
  while ((TWCR & (1<<TWINT)) == 0);
}

/**
 * Read a byte from the bus.
 * 
 * shouldAck: whether to send an ACK or a NACK.
 * returns: the byte read from the bus.
 */
uint8_t read(uint8_t shouldAck)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(shouldAck ? (1<<TWEA) : 0);
    while ((TWCR & (1<<TWINT)) == 0);
    return TWDR;
}

