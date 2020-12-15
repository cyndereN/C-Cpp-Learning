float var;
float setTemp = 25.00;       //default
float setpH = 5.0;           //default
int motorRPM = 1000;         //default
float curTemp = 30.00; 
float curpH = 7.00; 

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println("RPM, Temperature(C), pH");
}

void loop()
{
  while(Serial.available()>0)  //when serial available
  {
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
  delay(1000);
}
