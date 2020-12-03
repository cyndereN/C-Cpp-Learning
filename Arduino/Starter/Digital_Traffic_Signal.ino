int GreenLED = 10;
int YellowLED = 11;
int RedLED = 12;


void setup() {
  pinMode(GreenLED, OUTPUT);
  pinMode(YellowLED, OUTPUT);
  pinMode(RedLED, OUTPUT);

  digitalWrite(GreenLED,LOW);
  digitalWrite(YellowLED,LOW);
  digitalWrite(RedLED,LOW);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(GreenLED,LOW);
  digitalWrite(YellowLED,HIGH);
  digitalWrite(RedLED,LOW);

  Serial.println("Light Mode: Yield");
  delay(1000);

  digitalWrite(GreenLED,HIGH);
  digitalWrite(YellowLED,LOW);
  digitalWrite(RedLED,LOW);

  Serial.println("Light Mode: Go");
  delay(2000);

  digitalWrite(GreenLED,HIGH);
  digitalWrite(YellowLED,LOW);
  digitalWrite(RedLED,LOW);

  Serial.println("Light Mode: Stop");
  delay(3000);
}
