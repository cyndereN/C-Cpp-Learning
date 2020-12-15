/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/
char var;

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  while(Serial.available()>0)//when serial availabler
  {
    var = Serial.read();
    if(var == '1') digitalWrite(13,LOW);
    if(var == '2') digitalWrite(13,HIGH);
    if(var == '3') digitalWrite(13,LOW);
  }
}
