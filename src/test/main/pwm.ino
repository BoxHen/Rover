// This currently controls a LED for test purposes but we can connect to motors later
#define ledPin 9 // LED connected to digital pin 9

int analogPin = 3; // potentiometer connected to analog pin 3
int val = 0; // variable to store the read value

void setup() {
   pinMode(ledPin, OUTPUT); // sets the pin as output
}

void loop() {
   val = analogRead(analogPin); // read the input pin
   analogWrite(ledPin, (val / 4)); // value can be set to constant for specific speed or connected to some input to control motor speed
   /*
      analogWrite(pin, value)
      pin: the pin to write to. Allowed data types: int.
      value: the duty cycle: between 0 (always off) and 255 (always on). Allowed data types: int

      analogRead values go from 0 to 1023,
      analogWrite values from 0 to 255

      reference: https://www.tutorialspoint.com/arduino/arduino_pulse_width_modulation.htm
  */
}
