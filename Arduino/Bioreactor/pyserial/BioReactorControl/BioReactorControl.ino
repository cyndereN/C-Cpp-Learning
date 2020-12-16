/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/                    

float var;
float setTemp = 25.00;       //default
float setpH = 5.0;           //default
int motorRPM = 1000;         //default

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  while(Serial.available()>0)  //when serial available
  {
    var = Serial.readString().toFloat();
    if(var >= 500 && var <= 1500 ){    //New RPM
        motorRPM = var;
        Serial.println(motorRPM);
    }
    else if(var >= 20 && var <= 35){    //New Temperature
        setTemp = var;
        Serial.println(setTemp);
    }
    else if(var >= 3 && var <= 5){      //New pH
        setpH = var;
        Serial.println(setpH);
    }
    else{
          Serial.println("ERROR!!! Please input again.");
    }
  }
}
