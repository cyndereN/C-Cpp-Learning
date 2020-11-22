int pushButton = 12;

void setup(){
    Serial.begein(9600);
    pinMode(pushButton, INPUT);

}

void loop(){
    int buttonState = digitalRead(pushButton);

    if (buttonState == HIGH){
        Serial.println(buttonState);
    }
    
    delay(1);
}