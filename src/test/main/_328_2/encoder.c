// we don't need any other code since a a change on the pin will cause the interrupt and then the count++
ISR(INT0_vect){
  COUNT++;
}

ISR(INT1_vect){
  COUNT++;
}

void init_encoders(){
	DDRB = (1 << PB0); // output to other 328 based off COUNT value
  DDRB = ~(1 << PB7); //set as input for other 328

  // ENABLE EXTERNAL INTERRUPTS
	EIMSK  = 0x03;// turn on both INT0 and INT1
	EICRA  = 0x05;// any logic change on both will generate interrupt request

	sei();	// enable global interrupt
}

void turnCount(){
  if(PINC & (1 << PB7)){ // check if other 328 is requesting a count
    Temp = COUNT;
    Temp = COUNT - Temp; // this takes the current count and subtracts the previous count stored in Temp
    if(Temp >= turnValue){
      PORTB |= (1 << PB0);
    }
  }
}
