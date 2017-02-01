#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"



char* myBigArray[16383] = {"str1", "str2", "str1000"};
// factors of 16383
char* myBigDoubleArray[127][129] = {{"1", "2"}, {"3", "4"}};

const char myConstBigArray[9223372036854775807];
const char myConstBigDoubleArray[129][127];
const int a = 1;
int b = 1;
const int *c;
int *d;
char text[100];
void setup ()
{
  c = &a;
  d = &b;
  init();
  Serial.begin(9600);
  sprintf(text, "%d,%d", c, d);
  Serial.write(text);
  delay(50);
}

void loop () 
{

}


