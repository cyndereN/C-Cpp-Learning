#include <LiquidCrystal.h>

const int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;   //LCD set up
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

float var;                                //

const int LED = 13;
const int BUTTON = 7;
const int MORTOR = 10;
const int TEMP = 6;
const int TEMP_INPUT = A3;
//const int PH = 9;
//const int PH_INPUT = A2;
int motorOutputValue = 0;
int motorRPM = 1000;         //default
int oldmotorRPM = 0;
//int tempOutputValue = 0;
//int tempSensorValue = 0;
//int pHOutputValue = 0;
//int pHSensorValue = 0;
float setTemp = 25.00;       //default
float setpH = 5.0;           //default
float curTemp = 20.00; 
float curpH = 3.0; 
int buttonState;
/*

float baseError(int time, float cVal, float tVal){
  return cVal - tVal;
  //negative if under target, positive if above target
}

float derivativeError(int time, float prevError, float error){
  return (error-prevError);//one time unit
}
float* PID(int time=0,float cVal=20, float tVal=20, float prevError=0, float prevIntegral=0){
  //cTemp = current temp, tTemp = target temp
  float* valList = calloc(3);
  *(valList)=baseError(time,cVal,tVal);
  if (time!=0){
    *(valList+1)=prevIntegral + *(valList);//one time unit
    *(valList+2)=derivativeError(time,prevError,*(valList));
  }
  return valList;
}

*/

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(MORTOR, OUTPUT);
  //pinMode(PH, OUTPUT);
  //pinMode(TEMP, OUTPUT);
  //pinMode(PH_INPUT, INPUT);
  //pinMode(TEMP_INPUT, INPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
  Serial.println("RPM, Temperature(C), pH");      //For data sheet
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
    
    // Stirring system
    motorOutputValue = (motorRPM - 513/13)*13/500;  //to be calibrated
    //Serial.println(motorOutputValue);     
    //Serial.println(motorRPM);           //record data
    analogWrite(MORTOR, motorOutputValue); 
    
    // Temperature system
    /*
    //get temp, put into PID formula, adjust, loop
    float k[3] = {1.0,1.0,1.0};
    tempSensorValue = analogRead(TEMP_INPUT);
    //request user temperate = tVal
    float PIDvaluesList[3] = PID(time,tempSensorValue,tVal,prevError,prevIntegral);
    tempOutputValue = (k[0]*PIDvaluesList[0])+(k[1]*PIDvaluesList[1])+(k[2]*PIDvaluesList[2]);
    curTemp = tempSensorValue; //to be calibrated 
    if (curTemp < 25 || curTemp < setTemp)
    //	analogWrite(TEMP, tempOutputValue);
    if (curTemp > 35 || curTemp > setTemp) digitalWrite(TEMP, LOW);
    Serial.println(curTemp);
    */
    
    // pH system
    /*
    pHSensorValue = analogRead(PH_INPUT);
    pHOutputValue = Pid();
    curpH = pHSensorValue; //to be calibrated 
    if (curpH < 3 || curpH < setpH)
    	analogWrite(PH, pHOutputValue);
    if (curpH > 7 || curpH > setpH)
    	digitalWrite(PH, LOW);
    Serial.println(curpH);
    */
    
    
    // Change data via serial
    
    while(Serial.available()>0){//when serial available
        var = Serial.readString().toFloat();
        if(var >= 500 && var <= 1500 ){    //New RPM
            motorRPM = var;
            //Serial.println(motorRPM);
        }
        else if(var >= 20 && var <= 35){    //New Temperature
            setTemp = var;
            //Serial.println(setTemp);
        }
        else if(var >= 3 && var <= 7){      //New pH
            setpH = var;
            //Serial.println(setpH);
        }
        else{
            Serial.println("ERROR!!! Please input again.");
        }
  	}

	// Send data

    Serial.print(motorRPM);
    Serial.print(", ");
    Serial.print(curTemp);
    Serial.print(", ");
    Serial.println(curpH);
    // delay(1000);
    
    // Update LCD, print data on the actrual screen.
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
