#include "stdlib.h"

//tring to use as much of the dynamic memory as possible
//volatile char myBigArray[1850];
//volatile char myBigDoubleArray[50][37];

//these should be stored in flash so the size is limited the size of the address
const char myConstBigArray[32767];
const char myConstBigDoubleArray[151][217];

void setup ()
{
  char text[80];
  Serial.begin(9600);
  sprintf(text, "Hello world!");
  Serial.write(text);
}

void loop () 
{

}

