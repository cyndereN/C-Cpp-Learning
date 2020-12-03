int potpin = 0;
int ledpin = 11;
int val = 0;
void setup(){
	pinMode(ledpin,OUTPUT);
	Serial.begin(9600);
}

void loop(){
	val = analogRead(potpin); 
	val = 255 - val/2;  // 650-0     PWM 0-255    
        if(val < 0)
            val = 0;
	Serial.println(val);
	analogWrite(ledpin, val);
	delay(100);
}