int flame = A5;
int Beep = 8;
int val = 0;
void setup() {
	pinMode(Beep,OUTPUT);
	pinMode(flame,INPUT);
	Serial.begin(9600);
	val = analogRead(flame);
}

void loop() {  
	Serial.println(analogRead(flame));
	if((analogRead(flame) - val)>=600)
		digitalWrite(Beep,HIGH); 
    else
        digitalWrite(Beep,LOW);
}