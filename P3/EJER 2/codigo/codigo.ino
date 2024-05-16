int rojo = 0;
int last_pos = 0;
int pos = 0;
int cambiar = 0;

void setup()
{
  //Pines usados para los leds
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);

  //Pin en el que recibiremos la señal del interruptor
  pinMode(7, INPUT);

  //Establecemos el estado inicial (Rojo apagado, verde y amarillo encendidos)
  digitalWrite(13, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(11, LOW);
}

void loop()
{
  pos = digitalRead(7);
  
  //Comprobamos si el botón ha sido pulsado (Ya que la señal que se recibe es distinta a la última y esta señal es HIGH, es decir, esta siendo pulsado)
  //Si solo comprobaramos si el botón manda la señal HIGH, estaríamos cambiando los colores constantemente mientras mantenemos pulsado el botón
  if (pos != last_pos and pos == HIGH){
  	cambiar = 1;
  }
  else{
  	cambiar = 0;
  }
  
  //Cambiamos los leds que han de estar encendidos
  if (cambiar){
    if (rojo == 0){
      rojo = 1;
    }
    else{
      rojo = 0;
    }

    if (rojo == 1){
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(11, HIGH);
    }
    else{
      digitalWrite(13, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(11, LOW);
    }
  }
  
  last_pos = pos;
  
}
