void setup(){
    pinMode(7, INPUT);
}

void loop(){
    if(digitalRead(7)==HIGH) tone(11, 2000);
    else noTone(11);
}