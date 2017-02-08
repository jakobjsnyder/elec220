#include <stdio.h>
# define DEBUG_OUTPUT_MESSAGE_MAX_LENGTH 80

void floatread( int* ptr);

void setup ()
{
  Serial . begin (9600) ;
  char message [ DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ];
  
  float test = -1.0;
  int* ptr;
  ptr =(int*)&test;
  floatread(ptr);
}

void loop() {

}

void floatread( int* ptr)
{
  char message [ DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ];
  if (*ptr == 0) {
    snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ,
               "number is 0") ;
    Serial . write ( message ) ;
    return;
  }
  *ptr &= 0x80000000;

  if (*ptr == 0) {
    snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ,
               "positive number") ;
    Serial . write ( message ) ;
  }
  else {
    snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ,
               "negative number") ;
    Serial . write ( message ) ;
  }
}


