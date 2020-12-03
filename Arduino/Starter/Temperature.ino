//LM35

void setup(){
    Serial.begin(9600);
}

void loop(){
    Serial.println(analogRead(0)*0.48828125);
    delay(100);
}