int val = 0;
int LED = 13;
void setup(){
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
}

void loop(){
    val = Serial.read();
    if(val == 'R'){
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500);
        Serial.println("Hello World!");
    }
}
