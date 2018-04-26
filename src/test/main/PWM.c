#include "PWM.h"

void init_PWM(){
    // DDRD |= ((1<<5) | (1<<6)); // can be used for dynamic pwm
    TCCR0A |= ((1 << 7) | (1 << 5) | (1 << 1) | (1 << 0)); // 0 and 1 makes it a fast PWM with top as 0xFF/update on bottom
    // 7 and 5 Clears OC0B/OC0A on Compare Match when up-counting. Set OC0B/OC0A on Compare Match when down-counting.
    TCCR0B |= 1 << 0; // sets no Prescaling
}

void PWM_left(uint8_t value){
    OCR0A = value;
}
void PWM_right(uint8_t value){
    OCR0B = value;
}
    return 0;
