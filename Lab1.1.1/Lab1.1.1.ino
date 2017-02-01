# include "stdio.h"
#include <stdint.h>
# define DEBUG_OUTPUT_MESSAGE_MAX_LENGTH 80

void getVarSizes();

void setup () {
  // put your setup code here , to run once :
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

  getVarSizes();
}
void loop () {
  // put your main code here , to run repeatedly :
}

void getVarSizes() {
  char message [ DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ];
  char testChar;
  int testCharSize = 0;
  short testShort;
  int testShortSize = 0;
  int testInt;
  int testIntSize = 0;
  long testLong;
  int testLongSize = 0;
  long long testLongLong;
  int testLongLongSize = 0;

  char *addr1, *addr2;
  addr1 = (char*)&testChar;
  addr2 = (char*)(&testChar + 1);
  testCharSize = (int)(addr2 - addr1);

  addr1 = (char*)&testShort;
  addr2 = (char*)(&testShort + 1);
  testShortSize = (int)(addr2 - addr1);

  addr1 = (char*)&testInt;
  addr2 = (char*)(&testInt + 1);
  testIntSize = (int)(addr2 - addr1);

  addr1 = (char*)&testLong;
  addr2 = (char*)(&testLong + 1);
  testLongSize = (int)(addr2 - addr1);

  addr1 = (char*)&testLongLong;
  addr2 = (char*)(&testLongLong + 1);
  testLongLongSize = (int)(addr2 - addr1);

  snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH , "Experimental char size = %d size of = %d\n", testCharSize, sizeof(char));
  Serial . write ( message ) ;
  snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH , "Experimental short size = %d size of = %d\n", testShortSize, sizeof(short));
  Serial . write ( message ) ;
  snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH , "Experimental int size = %d size of = %d\n", testIntSize, sizeof(int));
  Serial . write ( message ) ;
  snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH , "Experimental long size = %d size of = %d\n", testLongSize, sizeof(long));
  Serial . write ( message ) ;
  snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH , "Experimental long long size = %d size of = %d\n\n", testLongLongSize, sizeof(long long));
  Serial . write ( message ) ;
}
