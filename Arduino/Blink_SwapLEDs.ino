/*
  This program blinks LED of the Arduino
*/
static const uint8_t LED = 8;
static const uint8_t LED1 = 13;


void setup()
{
  pinMode(LED1, OUTPUT);
}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  // turn the LED off (LOW is the voltage level)
  digitalWrite(LED, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}