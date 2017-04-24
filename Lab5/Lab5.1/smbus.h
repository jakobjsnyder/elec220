/** SMBus Interface Driver
 *  
 *  This .h file provides the function declarations that let you interact with SMBus-compliant devices
 *  using the i2C master mode of the AVR's TWI module.
 *  
 *  Do not modify these function declarations. You'll implement these functions in the corresponding
 *  smbus.cpp source file. 
 **/


/** Tell the compiler to only include this file once per compilation, 
 *  just in case it's included in multiple source files part of the same compilation. 
 *  The old way of doing this was with "include guards" (see https://en.wikipedia.org/wiki/Include_guard)
 **/
#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <avr/io.h>

void SMBUS_init();
uint8_t SMBUS_readRegister(uint8_t devAddr, uint8_t regAddr);
uint8_t SMBUS_writeRegister(uint8_t devAddr, uint8_t regAddr, uint8_t regVal);

// optional functions you can implement if you want to
uint16_t SMBUS_readRegisterWord(uint8_t devAddr, uint8_t regAddr);
void SMBUS_readRegister(uint8_t devAddr, uint8_t regAddr, uint8_t* buffer, size_t numBytesToRead);
