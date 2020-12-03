int outputValue = 0;
int sensorValue = 0;
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(A4, INPUT);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(13, HIGH);
  digitalWrite(5, HIGH);
  sensorValue = analogRead(A4);
  outputValue = map(sensorValue, 0, 1023, 0, 255);
  Serial.println(outputValue);
  analogWrite(3, outputValue);
}