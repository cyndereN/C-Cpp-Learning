void setup(){
    Serial.begin(9600);
    pinMode(9,OUTPUT);
}

void loop(){
    analogWrite(9,map(analogRead(0), 400, 700, 0, 255));
    delay(100);
}