# include "ledArray.h"

void setup () {
  ledArray_init();
}
void loop () {
  for (int i = 0; i < 16; i ++) {
    ledArray_clear () ;
    ledArray_setPin (i , true ) ;
    ledArray_flush () ;
    delay (100) ;
  }
}

