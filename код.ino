#include <Servo.h>

Servo horizontal;
int servoh = 102; // Задаем начальный угол для сервопривода оси Х

int servohLimitHigh = 180; // Максимальный угол
int servohLimitLow = 10; // Минимальный угол

Servo vertical;
int servov = 120; // Задаем начальный угол для сервопривода оси Y

int servovLimitHigh = 180; // Максимальный угол
int servovLimitLow = 10; // Минимальный угол

int ldrlt = A2; //LDR top left - BOTTOM LEFT // Подключаем нижний левый фотоезистор
int ldrrt = A3; //LDR top rigt - BOTTOM RIGHT // Подключаем нижний правый фотоезистор
int ldrld = A0; //LDR down left - TOP LEFT // Подключаем верхний левый фотоезистор
int ldrrd = A1; //LDR down rigt - TOP RIGHT // Подключаем верхний правый фотоезистор

int buzz_pin = 10;
int buzz_tone = 20;

int tol = 50;

void setup()
{
  Serial.begin(9600);
  pinMode(buzz_pin, OUTPUT);
  horizontal.attach(7); // Подключаем сервопривод оси Х
  vertical.attach(4); // Подключаем сервопривод оси Y
  horizontal.write(servoh); // Даем имя сервоприводам
  vertical.write(servov); // Даем имя сервоприводам
}

void loop()
{
  int lt = analogRead(ldrlt); // верхний левый
  int rt = analogRead(ldrrt); // верхний правый
  int ld = analogRead(ldrld); // нижний левый
  int rd = analogRead(ldrrd); // нижний правый

  int avt = (lt + rt) / 2; // среднее значение сверху
  int avd = (ld + rd) / 2; // среднее значение снизу
  int avl = (lt + ld) / 2; // среднее значение слева
  int avr = (rt + rd) / 2; // среднее значение справа

  int dvert = abs(avt - avd); // проверить разницу значений и опустить или поднять
  int dhoriz = abs(avl - avr);// проверить разницу значений и повернуть вправо или влево

  Serial.print("avt: ");
  Serial.print(avt);
  Serial.print(" ");
  Serial.print("avd: ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print("avl: ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print("avr: ");
  Serial.println(avr);

  Serial.print("h: ");
  Serial.print(servoh);
  Serial.print(" ");
  Serial.print("v: ");
  Serial.print(servov);
  Serial.print(" ");

  if (dhoriz > tol)
  {
    if (avl > avr)
    {
      if (servoh - 1 >= servohLimitLow) servoh--;
      else beep(120);
    }
    else if (avl < avr)
    {
      if (servoh + 1 <= servohLimitHigh) servoh++;
      else beep(120);
    }
    horizontal.write(servoh);
  }

  if (dvert > tol)
  {
    if (avt > avd)
    {
      if (servov + 1 <= servovLimitHigh) servov++;
      else beep(100);
    }
    else if (avt < avd)
    {
      if (servov - 1 >= servovLimitLow) servov--;
      else beep(100);
    }
    vertical.write(servov);
  }
}


void beep(unsigned char delayms){
  analogWrite(buzz_pin, buzz_tone);
  delay(delayms);
  analogWrite(buzz_pin, 0);
  delay(delayms);   
}
