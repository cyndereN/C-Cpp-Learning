int switchpin = A5;
int ledpin = 8;
int val = 0;
void setup() { 
    pinMode(ledpin,OUTPUT);
    Serial.begin(9600);
} 
void loop() { 
    val = analogRead(switchpin);
	if(val>512)
		digitalWrite(ledpin,HIGH);
	else
		digitalWrite(ledpin,LOW);//拉低 
    Serial.println(val);
} 