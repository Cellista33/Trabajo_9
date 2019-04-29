#define trigPin1 13
#define echoPin1 12
#define trigPin2 11
#define echoPin2 10
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
LiquidCrystal_I2C lcd(0x27, 20, 4);
void setup()
{
  Serial.begin (9600);
  lcd.init();
  lcd.backlight();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(led, OUTPUT);
  pinMode(zum, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(v, OUTPUT);
  pinMode(r, OUTPUT);
}

void loop()
{
  long frecuencia, duracion_1, duracion_2, distancia_1, distancia_2;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duracion_1 = pulseIn(echoPin1, HIGH);
  distancia_1 = (duracion_1 / 2) / 29.1;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  duracion_2 = pulseIn(echoPin2, HIGH);
  distancia_2 = (duracion_2 / 2) / 29.1;


  if (distancia >= 200 || distancia <= 0)
  {
    Serial.println("Fuera de rango");
    lcd.setCursor(0, 0);
    lcd.print("");
    delay(500);
    analogWrite(v, 255);
    analogWrite(r, 0);
    analogWrite(a, 0);
  }

  else
  {
    Serial.print(distancia_1);
    Serial.print(distancia_2);
    lcd.setCursor(0, 0);
    lcd.print("Dist_F: ");
    lcd.print(distancia_1);
    lcd.print(" cm");
    lcd.setCursor(0, 1);
    lcd.print("Dist_B: ");
    lcd.print(distancia_1);
    lcd.print(" cm");
    frecuencia = distancia_1;
    zumba(map(frecuencia, 10, 200, 1, 12), map(distancia, 10, 200, 50, 500));
    contrRGB(distancia_2);

  }
  lcd.clear();
}

void zumba (int frecuencia, int duracion_1)
{
  tone(zum, vNotas[frecuencia]);
  delay(duracion_1);
  noTone(zum);
  delay(duracion_1);
}

void contrRGB (int distancia_2)
{
  if (distancia_2 < 10)
  {
    analogWrite(r, 255);
    analogWrite(v, 0);
    analogWrite(a, 0);
  }

  else
  {
    if (distancia_2 <= 30)
    {
      analogWrite(r, 255);
      analogWrite(v, 0);
      analogWrite(a, 0);
    }

    if (distancia_2 >= 20 && distancia_2 < 200)
    {
      analogWrite(v, 248);
      analogWrite(r, 243);
      analogWrite(a, 43);
    }
    delay(map(distancia_2, 10, 200, 50, 500));
    analogWrite(r, 0);
    analogWrite(v, 0);
    analogWrite(a, 0);
    delay(map(distancia_2, 10, 200, 50, 500));
  }
}
