# define DEBUG_OUTPUT_MESSAGE_MAX_LENGTH 80

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

  char testCharArray[80] = "Test Sentence #1";
  char* ptr = testCharArray;
  myToUpper(ptr);
   snprintf ( message , DEBUG_OUTPUT_MESSAGE_MAX_LENGTH ,
             testCharArray) ;
  Serial . write ( message ) ;
}
void loop () {
  // put your main code here , to run repeatedly :
}

void myToUpper(char* pointer) {
  int i = 0;
  for (i = 0; i < 80; i++) {
    if (pointer[i] == '\0')
      return;
    if ((int)pointer[i] >= 97 && (int)pointer[i] <= 122)
      pointer[i] -= 32;
  }
}


