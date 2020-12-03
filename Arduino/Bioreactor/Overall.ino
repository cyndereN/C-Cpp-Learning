#include <LiquidCrystal.h>
const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const int LED = 13;
const int BUTTON = 7;
const int MORTOR = 10;
const int MORTOR_INPUT = A4;
int motorOutputValue = 0;
int motorSensorValue = 0;    //Change RPM mannually
int motorRPM = 1000;         //default
int oldmotorRPM = 0;
float setTemp = 25.00;       //default
float setpH = 5.0;           //default
float curTemp = 20.00; 
float curpH = 3.0; 
int buttonState;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(MORTOR, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  // LCD
  lcd.begin(24, 2);
  lcd.print("Hello, world!");
}

void loop()
{
  int oldmotorRPM = motorRPM;
  buttonState = digitalRead(BUTTON);
  if (buttonState == HIGH){
    //Serial.println(buttonState);
    digitalWrite(LED, HIGH);
    motorSensorValue = analogRead(MORTOR_INPUT);
    motorOutputValue = map(motorSensorValue, 0, 1023, 12, 39);  //to be calibrated
    motorRPM = motorOutputValue*500/13+513/13;    //to be calibrated
    //Serial.println(motorOutputValue);     
    Serial.println(motorRPM);           //record data
    analogWrite(MORTOR, motorOutputValue); 
    
    //Update LCD
    lcd.setCursor(0, 0);
    if (motorRPM != oldmotorRPM)  lcd.clear();
    lcd.print("Current ");
    lcd.print("RPM:");
    lcd.print(motorRPM);
    lcd.print(" ");
    lcd.print("Temp: ");
    lcd.print(curTemp);
    lcd.print(" ""C ");
    lcd.print("pH: ");
    lcd.print(curpH);
    lcd.print("    ");
    lcd.scrollDisplayLeft();
    
    lcd.setCursor(0, 1);
    lcd.print("Set     ");
    lcd.print("RPM:");
    lcd.print(motorRPM);
    lcd.print(" ");
    lcd.print("Temp: ");
    lcd.print(setTemp);
    lcd.print(" ""C ");
    lcd.print("pH: ");
    lcd.print(setpH);
    lcd.print("    ");
    lcd.scrollDisplayLeft();
  }
  else{
    digitalWrite(LED, LOW);
    motorOutputValue = 0;
    analogWrite(MORTOR, motorOutputValue);
  }
}
