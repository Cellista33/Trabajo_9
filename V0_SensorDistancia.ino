#define trigPin 13                            //Definimos los pinjes a que se conectarán Trigg y Echo en el Arduino
#define echoPin 12

void setup() {
  Serial.begin (9600);                        //Inicializamos el monitor serie
  pinMode(trigPin, OUTPUT);                   //Declaramos Trig como salida y Echo como entrada
  pinMode(echoPin, INPUT);

}

void loop() {
  long frecuencia, duracion, distancia;       //Declaramos las variables que vamos a utilizar en el código
  digitalWrite(trigPin, LOW);                 //Nos aseguramos de que el disparo comience cada ciclo en 0
  delayMicroseconds(2);                       //Esperamos unos ms a que sea efeciva
  digitalWrite(trigPin, HIGH);                //Lanzamos la señal de disparo al sensor

  delayMicroseconds(10);                      //Mantenemos la señal de disparo 10 ms activa...
  digitalWrite(trigPin, LOW);                 //... y detenemos el pulso.
  
  duracion = pulseIn(echoPin, HIGH);          //Guardamos el tiempo recibido por Echo en "duracion".
  distancia = (duracion/2) / 29.1;            //Calculamos la distancia a partir del tiempo recibido.

  if (distancia >= 200 || distancia <= 0)     //Si la distancia medida está fuera del rango acordado...
  {
    Serial.println("Fuera de rango");         //... así lo indicamos en el monitor serie.
  }
  
  else                                        //En caso contrario...
  {
    Serial.print(distancia);                  //Sacamos por pantala la distancia medida en cm.
    Serial.println(" cm");
  }
}
