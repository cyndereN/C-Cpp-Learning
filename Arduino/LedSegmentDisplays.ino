class LedSegmentDisplays
{
  private:
    int ports[8];
    int digits[10][8];
    
  public:
    LedSegmentDisplays(int a, int b, int c, int d, int e, int f, int g, int h)
    {
      ports[0] = a; ports[1] = b; ports[2] = c; ports[3] = d; ports[4] = e; ports[5] = f; ports[6] = g; ports[7] = h;
      int digits_copy[10][8] = { 
        {1, 1, 1, 1, 1, 1, 0, 0},  // 0
        {0, 1, 1, 0, 0, 0, 0, 0},  // 1
        {1, 1, 0, 1, 1, 0, 1, 0},  // 2
        {1, 1, 1, 1, 0, 0, 1, 0},  // 3
        {0, 1, 1, 0, 0, 1, 1, 0},  // 4
        {1, 0, 1, 1, 0, 1, 1, 0},  // 5
        {1, 0, 1, 1, 1, 1, 1, 0},  // 6
        {1, 1, 1, 0, 0, 0, 0, 0},  // 7
        {1, 1, 1, 1, 1, 1, 1, 0},  // 8
        {1, 1, 1, 1, 0, 1, 1, 0}   // 9
      };
      
      for(int i = 0; i < 8; i++)
        pinMode(ports[i], OUTPUT);
      
      for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
          digits[i][j] = digits_copy[i][j];
    }
    
    void noLight() 
    { 
      for(int i = 0; i < 8; i++)
        digitalWrite(ports[i], LOW);
    }
    
    void d(int digit) 
    { 
      for(int i = 0; i < 8; i++)
        digitalWrite(ports[i], digits[digit][i]);
    }
};

void setup() {
  randomSeed(analogRead(0));
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
}

LedSegmentDisplays Disp(3,10,7,8,9,4,5,6);

void loop() {
  if(digitalRead(2) == LOW)
    Disp.d(random(1,7));  // [1,6]
    
  delay(20);
}


