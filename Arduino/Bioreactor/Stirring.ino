const int LED = 13;
const int BUTTON = 7;
const int MORTOR = 3;
const int MORTOR_INPUT = A4;


int motorOutputValue = 0;
int motorSensorValue = 0;    //Change RPM mannually
int motorRPM = 0;           //default     
int buttonState;
void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(MORTOR, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop()
{
  buttonState = digitalRead(BUTTON);
  if (buttonState == HIGH){
    //Serial.println(buttonState);
    digitalWrite(LED, HIGH);
    motorSensorValue = analogRead(MORTOR_INPUT);
    motorOutputValue = map(motorSensorValue, 0, 1023, 12, 39);  //to be calibrated
    motorRPM = motorOutputValue*500/13+513/13;    //to be calibrated
    //Serial.println(motorOutputValue);     
    Serial.println(motorRPM);           //record data every 2 seconds
    analogWrite(MORTOR, motorOutputValue);    
    delay(2000);
  }
  else{
    digitalWrite(LED, LOW);
    motorOutputValue = 0;
    analogWrite(MORTOR, motorOutputValue);
  }
}