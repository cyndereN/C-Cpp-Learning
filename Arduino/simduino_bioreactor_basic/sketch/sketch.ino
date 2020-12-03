/*
 sketch.ino

 Stephen Hailes, Oct 2020

 This is a template sketch for the testboard simduino
  
 */

#include <stdio.h>
#include <string.h>

// These define which pins are connected to what device on the virtual testboard
// The descriptions are all from the perspective of the arduino
//
const byte lightgatePin  = 2;    // This is pin D2 on the AVR
const byte stirrerPin    = 5;    // This is pin D5 on the AVR
const byte heaterPin     = 6;    // This is pin D6 on the AVR
const byte thermistorPin = A0;   // This is pin C0 on the AVR


void setup() {
  Serial.begin(9600);
  Serial.println("Hello World");

  pinMode(lightgatePin,  INPUT);
  pinMode(stirrerPin,    OUTPUT);
  pinMode(heaterPin,     OUTPUT);
  pinMode(thermistorPin, INPUT);

  // More setup...
  
}

 
void loop() {

  // Do something...

}
