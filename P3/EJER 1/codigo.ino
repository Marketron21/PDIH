void setup()
{
  //Indicamos que los pines 11, 12 y 13 serán usados para salida
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  //Encendemos durante 1.5 segundos el led conectado al pin 13
  digitalWrite(13, HIGH);
  delay(1500);
  digitalWrite(13, LOW);
  
  //Encendemos durante 1.5 segundos el led conectado al pin 12
  digitalWrite(12, HIGH);
  delay(1500);
  digitalWrite(12, LOW);
  
  //Encendemos durante 1.5 segundos el led conectado al pin 11
  digitalWrite(11, HIGH);
  delay(1500);
  digitalWrite(11, LOW);
}
