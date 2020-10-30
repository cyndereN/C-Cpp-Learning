void setup()
{
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(2, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  digitalWrite(5, LOW);
  digitalWrite(2, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}