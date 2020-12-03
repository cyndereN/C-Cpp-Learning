void setup(){
    pinMode(3,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
}

int level = 1;
int ports[6] = {3, 5, 6, 9, 10, 11};
int idx = 0;

void loop(){

    analogWrite(port[idx], level);
    delay(10);
    ++level %= 7;  // if(level>6) level=0;
    ++idx %= 6;

}