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
}
void loop () {
// put your main code here , to run repeatedly :
}

