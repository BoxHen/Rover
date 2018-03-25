#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>

//On TCCR0A
#define pwm_coma1 7
#define pwm_coma0 6
#define pwm_comb1 5
#define pwm_comb0 4

#define pwm_wgm0 0
#define pwm_wgm1 1

//On TCCR0B
#define pwm_wgm2 3

#define pwm_cs0 0
#define pwm_cs1 1
#define pwm_cs2 2



int main (){

    //set the PORTD 5&6 as output
    DDRD |= ((1<<5) | (1<<6));
	
    //Set WGM(2:0) 	= 3 Fast FWM with TOP as FF
    //Set COM0A(1:0) 	= 2 Clear OC0A on compare match, Set on BOTTOM
    //Set CS(2:0)	= 1 Use clock with no Prescaling

    TCCR0A |= ((1 << pwm_wgm0) | (1 << pwm_wgm1) | (1 << pwm_coma1) | (1 << pwm_comb1));
	
    //TCCR0B &= 0x00;
    TCCR0B |= (1 << pwm_cs0);
    
    while (1){
        
        OCR0A = 0xB2;
        OCR0B = 0x7F; //Insert your code here
        
    }
    
    return 0;
    
}