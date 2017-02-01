#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"


void setup ()
{
  volatile float var;
  int i;
  long t, before, after;
  char text[80];
  Serial.begin(9600);
  i = 0;
  var = 1.0;
  before = micros();
  while (i < 1000)
  {
    var *= 2;
    i++;
  }
  after = micros();
  t = (after - before);
  sprintf (text, "it took %d microseconds\n", t);
  Serial.write(text);
  delay(50);
}

void loop() {

}

