#define trigPin 13
#define echoPin 12
#define led 11
#define zum 6
#define r 5
#define v 4
#define a 3

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

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
LiquidCrystal_I2C lcd(0x27,20,4);
void setup()
{
  Serial.begin (9600);
   lcd.init();   
    lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(zum, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(v, OUTPUT);
  pinMode(r, OUTPUT);
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
  distancia = (duracion / 2) / 29.1;


  if (distancia >= 200 || distancia <= 0)
  {
    Serial.println("Fuera de rango");
    lcd.setCursor(0,0);
    lcd.print("Yo controlo");
    delay(500);
    analogWrite(v, 255);
    analogWrite(r, 0);
    analogWrite(a, 0);
  }

  else
  {
    Serial.print(distancia);
    lcd.setCursor(0,0);
    lcd.print("Dist: ");
    lcd.print(distancia);
    Serial.println(" cm");
    lcd.print(" cm");
    lcd.setCursor(0,1);
    lcd.print("#");
    frecuencia = distancia;
    zumba(map(frecuencia, 10, 200, 1, 12), map(distancia, 10, 200, 50, 500));
    contrRGB(distancia);
    
  }
  //delay(500);
  lcd.clear();
}

void zumba (int frecuencia, int duracion)
{
  tone(zum, vNotas[frecuencia]);
  delay(duracion);
  noTone(zum);
  delay(duracion);
}

void contrRGB (int distancia)
{
  if (distancia < 10)
  {
    analogWrite(r, 255);
    analogWrite(v, 0);
    analogWrite(a, 0);
  }

  else
  {
    if (distancia <= 30)
    {
      analogWrite(r, 255);
      analogWrite(v, 0);
      analogWrite(a, 0);
    }

    if (distancia >= 20 && distancia < 200)
    {
      analogWrite(v, 248);
      analogWrite(r, 243);
      analogWrite(a, 43);
    }
    delay(map(distancia, 10, 200, 50, 500));
    analogWrite(r, 0);
    analogWrite(v, 0);
    analogWrite(a, 0);
    delay(map(distancia, 10, 200, 50, 500));
  }
}
