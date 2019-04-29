#define trigPin 13
#define echoPin 12
#define led 11
#define zum 6

int DO = 131;
int DOS = 139;
int RE = 147;
int RES = 156;
int MI = 165;
int FA = 175;
int FAS = 185;
int SOL = 196;
int SOLS = 208;
int LA = 220;
int LAS = 233;
int SI = 247;

int vNotas[12] = {DO, DOS, RE, RES, MI, FA, FAS, SOL, SOLS, LA, LAS, SI};

void setup() 
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(zum,OUTPUT);
}

void loop() 
{
  long frecuencia, duracion, distancia;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  
  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion/2) / 29.1;
 
 
  if (distancia >= 200 || distancia <= 0)
  {
    Serial.println("Fuera de rango");
  }
  
  else 
  {
    Serial.print(distancia);
    Serial.println(" cm");
    frecuencia = distancia;
    zumba(map(frecuencia,10,200,1,12), map(distancia,10,200,50,500));
  }
  //delay(500);
}

void zumba (int frecuencia, int duracion)
{
  tone(zum, vNotas[frecuencia]);
  delay(duracion);
  noTone(zum);
  delay(duracion);
}
