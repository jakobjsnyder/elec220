#include <stdio.h>
# define DEBUG_OUTPUT_MESSAGE_MAX_LENGTH 80

void floatread( int* ptr);

void setup ()
{
  Serial . begin (9600) ;
  char message [ DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ];
  unsigned long begin_time ;
  unsigned long end_time ;
  begin_time = micros () ;
  snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH , "Hello , World !\n") ;
  Serial . write ( message ) ;
  end_time = micros () ;
  snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ,
             "It took %d microseconds to generate and send ’Hello World ! ’\n",
             end_time - begin_time ) ;
  Serial . write ( message ) ;

  float test = -1.0;
  int* ptr = &test;
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


