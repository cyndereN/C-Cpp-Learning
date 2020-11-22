int pushButton = 12;
int LED == 3;

void setup(){
    Serial.begein(9600);
    pinMode(pushButton, INPUT);
    pinMode(LED, OUTPUT);
}

void loop(){
    int buttonState = digitalRead(pushButton);

    if (buttonState == HIGH){
        digitalWrite(LED, HIGH);
        Serial.println(buttonState);
    }else{
        digitalWrite(LED, LOW);
    }
    
    delay(1);
}