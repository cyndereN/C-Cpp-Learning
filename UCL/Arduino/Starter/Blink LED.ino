int LED = 9;
int counter = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  counter = counter + 100; // adding one every loop
  Serial.print("BLink Number #");
  Serial.println(counter);
  digitalWrite(LED,HIGH);
  delay(1000-counter);
  digitalWrite(LED,LOW);
  delay(1000-counter);
}
