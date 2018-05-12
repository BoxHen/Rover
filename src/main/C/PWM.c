#include "PWM.h"

void init_PWM(){
    DDRD |= ((1<<3) | (1<<5) | (1<<6)); // OC2B, OC0B, OC0A --THESE CONNECT TO MOTORS--
	DDRB |= (1<<3); // OC2A
	
    TCCR0A |= ((1 << 7) | (1 << 5) | (1 << 1) | (1 << 0)); // 0 and 1 makes it a fast PWM with top as 0xFF/update on bottom
    // 7 and 5 Clears OC0B/OC0A on Compare Match when up-counting. Set OC0B/OC0A on Compare Match when down-counting.
    TCCR0B |= 1 << 0; // sets no Prescaling
	TCCR2A = ((1 << 7) | (1 << 5) | (1 << 1) | (1 << 0)); // same as above
    TCCR2B |= 1 << 0; // sets no Prescaling
}

void PWM_leftA(uint8_t value){
    OCR0A = value;
}
void PWM_rightA(uint8_t value){
    OCR0B = value;
}
void PWM_leftB(uint8_t value){
    OCR2A = value;
}
void PWM_rightB(uint8_t value){
    OCR2B = value;
}



