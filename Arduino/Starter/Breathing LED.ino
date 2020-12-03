void setup(){
    pinMode(11, OUTPUT);
}

void loop(){
    for(int i=0;i<31;i++){
        analogWrite(11, i); // [0,255]
        delay(100);
    }

    for(int i=30;i>-1;i--){
        analogWrite(11, i); // [0,255]
        delay(100);
    }
}