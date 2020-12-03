int BASE = 2 ;  
int NUM = 6;   
int i=0;
void setup()
{
   for (int i = BASE; i < BASE + NUM; i ++) 
   {
     pinMode(i, OUTPUT);   
   }
}

void loop()
{
   for (i = BASE; i < BASE + NUM; i ++) 
   {
     digitalWrite(i, LOW);    
     delay(200);        
   }
   for (i = BASE; i < BASE + NUM; i ++) 
   {
     digitalWrite(i, HIGH);    
     delay(200);        
   }  
}
