#include <avr/interrupt.h>
#include <avr/io.h>
#include "palier.h"
 
byte j = 0; //variable passage temps
const byte ledverte = 4;
const byte ledorange = 2;
const byte ledrouge = 3;
byte  tpsminute = 0;
long compteur = 0;
unsigned long seconde = 0;
int temps = 0;
 
float n = 0;
byte palier[] = {50, 75, 80, 85}; //t°C des paliers
byte tpspalier[] = {1, 1, 1, 1};//tps en minute des paliers
unsigned long compteurpalier[4]; //tableau du calcul des debordement pour les palier
 
void setup() {
  byte i = 0;
  //calcul des temps compteur pour les paliers
  for (i = 0; i <= 4; i++)
  {
    compteurpalier[i] = tpspalier[i] * 20; // en seconde
  }
 
  //______registre
  cli();
  TCCR2A = 0b00000000;
  TCCR2B = 0b00000111;
  TIMSK2 = 0b00000001;
  TIFR2 = 0b00000000;
  OCR2A = 0b00000000;
  sei();
 
  pinMode(ledverte, OUTPUT);
  pinMode(ledorange, OUTPUT);
  pinMode(ledrouge, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(ledverte, LOW);
  digitalWrite(ledorange, LOW);
  digitalWrite(ledrouge, LOW);
  Serial.begin(9600);
  Serial.print(j);
}
 
ISR(TIMER2_OVF_vect)
{
  compteur = compteur + 1;
  if (compteur >= 125)
  { seconde = seconde + 1;
    compteur = 0;
  }
  TCNT2 = 130;
}
//_________fonction lire le potar renvoyé niveau
int temperature()
{
  int niveau = map(analogRead(0), 0, 1023, 0, 100);
  return niveau;
}
 
//______fonction allumé la lumière en fonction du niveau
void lumiere()
{
  int niveau = map(analogRead(0), 0, 1023, 0, 100);
  if (niveau >= (palier[j] - 2) && niveau <= (palier[j] + 2))
  {
    digitalWrite(ledverte, HIGH);
    digitalWrite(ledorange, LOW);
    digitalWrite(ledrouge, LOW);
  }
  else if (niveau > (palier[j] - 8) && niveau < (palier[j] - 2))
  {
    digitalWrite(ledverte, LOW);
    digitalWrite(ledorange, HIGH);
    digitalWrite(ledrouge, LOW);
  }
  else if (niveau > (palier[j] + 2))
  {
    digitalWrite(ledverte, LOW);
    digitalWrite(ledorange, LOW);
    digitalWrite(ledrouge, HIGH);
  }
  else {
    digitalWrite(ledverte, LOW);
    digitalWrite(ledorange, HIGH);
    digitalWrite(ledrouge, HIGH);
  }
}
 
void loop() {
  lumiere();
  temps = seconde;
  int niveau = map(analogRead(0), 0, 1023, 0, 100);
 
  // int niveau = map(analogRead(0), 0, 1023, 0, 100);
 
  if (niveau >= (palier[j] - 2) && niveau <= (palier[j] + 2))
  {
    temps = 0;
    seconde = 0;
  }
  
  int niveau2 = getTemperature();
  do
  {
    lumiere();
    niveau2 = getTemperature();
    Serial.print("temps ");
    Serial.println(temps);
    Serial.print("seconde ");
    Serial.println(seconde);
    Serial.print("niveau ");
    Serial.println(niveau2);
    temps = seconde + 1;
  }
  while (niveau2 >= (palier[j] - 2) && niveau2 <= (palier[j] + 2));
 
 
  Serial.print("j ");
  Serial.println(j,DEC);
  Serial.print("niveau ");
  Serial.println(niveau);
  Serial.print("palier ");
  Serial.println(palier[j]);
  Serial.print("seconde ");
  Serial.println(seconde);
  Serial.print("temps ");
  Serial.println(temps);
  Serial.print("compteur palier ");
  Serial.println(compteurpalier[j]);
 
 
  delay(2000);
 
}
 
int getTemperature() {
  return map(analogRead(0), 0, 1023, 0, 100);;
}

