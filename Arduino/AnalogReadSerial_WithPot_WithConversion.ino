/*
  AnalogReadSerial
  Reads an analog input (potentiometer) on pin 0,
  prints the result to the serial monitor.

  OPEN THE SERIAL MONITOR TO VIEW THE OUTPUT FROM
  THE POTENTIOMETER >>

  Attach the center pin of a potentiometer to pin
  A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

int sensorValue = 0;
float voltage = 0;

void setup()
{
  pinMode(A1, INPUT);
  Serial.begin(9600);

}

void loop()
{
  // read the input on analog pin 0:
  sensorValue = analogRead(A4);
  // print out the value you read:
  voltage = sensorValue * 5.0 / 1024;
  Serial.println(voltage);
  delay(500); // Delay a little bit to improve simulation performance
}