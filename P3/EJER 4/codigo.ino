// C++ code
//
int duration;
int distance;

void setup()
{
  pinMode(12, OUTPUT);
  pinMode(7, INPUT);
}

void loop()
{
  duration = pulseIn(7, HIGH);
  distance = (duration/2) / 29.1;
  
  if (distance < 302){
  	tone(12,5000, 200);
  }
}