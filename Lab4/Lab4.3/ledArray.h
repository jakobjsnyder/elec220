#pragma once
#include <stdint.h>
#include <stdbool.h>
void ledArray_init() ;
void ledArray_setPin( uint8_t pin , bool state ) ;
void ledArray_clear() ;
void ledArray_flush() ;
