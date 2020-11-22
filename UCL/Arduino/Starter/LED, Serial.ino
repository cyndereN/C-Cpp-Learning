int LED = 13;
int counter=0;
void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  counter = counter + 1; // adding one every loop
  Serial.print("BLink Number #");
  Serial.println(counter);
  digitalWrite(LED,HIGH);
  delay(1000);
  digitalWrite(LED,LOW);
  delay(500);
}
