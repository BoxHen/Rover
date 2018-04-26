#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "encoder.h"

while(1){
  init_encoders();
  turnCount();

  change = COUNT;
  if(COUNT != change){ // only prints COUNT if there is a change
    printf("COUNT IS: %d, ", COUNT);
  }
}
