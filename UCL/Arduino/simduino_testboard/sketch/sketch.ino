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
const byte pwmIn          = 2;   // This is a PWM input to us from the testboard
const byte LED1           = 4;   // This is a digital output connected to LED1
const byte LED2           = 5;   // This is a PWM output connected to LED2
const byte LED3           = 6;   // This is a PWM output connected to LED3
const byte analogue1      = A0;  // This is an analogue input from the testboard
const byte analogue2      = A1;  // This is a second analogue input from the testboard


void setup() {
  Serial.begin(9600);
  Serial.println("Hello World");

  pinMode(pwmIn,     INPUT);
  pinMode(LED1,      OUTPUT);
  pinMode(LED2,      OUTPUT);
  pinMode(LED3,      OUTPUT);
  pinMode(analogue1, INPUT);
  pinMode(analogue2, INPUT);

  // More setup...
  
}

 
void loop() {

  // Do something...

}
