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

byte espacio[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
};
byte col_1[8] = {
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
};
byte col_2[8] = {
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
};
byte col_3[8] = {
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
};
byte col_4[8] = {
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
};
byte col_5[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

int vNotas[12] = {DO, DOS, RE, RES, MI, FA, FAS, SOL, SOLS, LA, LAS, SI};
LiquidCrystal_I2C lcd(0x27, 20, 4);
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
  lcd.createChar(0, espacio);
  lcd.createChar(1, col_1);
  lcd.createChar(2, col_2);
  lcd.createChar(3, col_3);
  lcd.createChar(4, col_4);
  lcd.createChar(5, col_5);
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
    lcd.setCursor(0, 0);
    lcd.print("Yo controlo");
    delay(500);
    analogWrite(v, 255);
    analogWrite(r, 0);
    analogWrite(a, 0);
  }

  else
  {
    Serial.print(distancia);
    Serial.println(" cm");
    frecuencia = distancia;
    zumba(map(frecuencia, 10, 200, 1, 12), map(distancia, 10, 200, 50, 500));
    contrRGB(distancia);
    LCD(distancia);
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

void LCD (int distancia)
{
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distancia);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  map(distancia, 10, 200, 0, 80);
  int entero = (distancia / 5) - 1;
  for (int i = 0; i <= entero; i++)
  {
    lcd.write(byte(5));
  }
  
  int sobra = distancia - 5 * entero;
  lcd.write(byte(sobra));
  delay(500);
}
