#include <ESP32Servo.h>                             // Erstes include im Sketch

int servoPin = 10;                                  // GPIO für den Servo

const int Motor_links_A_Pin = 4; // 4 = GPIO8       // Der Variablenname darf nicht verändert werden, der GPIO schon
const int Motor_links_B_Pin = 1; // 5 = GPIO1       // Der Variablenname darf nicht verändert werden, der GPIO schon
const int Motor_rechts_A_Pin = 3; // 6 = GPIO2      // (Violet blau) Der Variablenname darf nicht verändert werden, der GPIO schon
const int Motor_rechts_B_Pin = 2; // 7 = GPIO3      // Der Variablenname darf nicht verändert werden, der GPIO schon
const int bodensensorPin = 5;
const int RoteLED = 7;

#include "PWM.h"                                    // Einbinden der PWM.h-Datei 

Servo myservo;                                      // Die Instanz myservo erzeugen

ESP32PWM ledPWM;
void setup() 
{

  PWM_init();

  myservo.setPeriodHertz(50);      // Perioden-Dauer einstellen
  myservo.attach(servoPin);

  PWM_analogWrite(Motor_rechts_A_Pin,0);            // Beide Motoren auf Geschwindigkeit Null setzen
  PWM_analogWrite(Motor_rechts_B_Pin,0);
  PWM_analogWrite(Motor_links_A_Pin,0);
  PWM_analogWrite(Motor_links_B_Pin,0);

  pinMode(RoteLED, OUTPUT);
  pinMode(bodensensorPin, INPUT);

  digitalWrite(RoteLED, LOW);
  ledPWM.attachPin(RoteLED, 1000, 8);
  ledPWM.write(0);
}

void loop() 
{
  if (sensor() > 2000)
  {
    digitalWrite(RoteLED, HIGH);
  }
  else{
    ledPWM.write(128);     // abeba ist ein genie4
  }
  
  
}

int sensor(){
  int wert = analogRead(bodensensorPin);
  return wert;
}
void turn(int winkel){                                                                          // noch genauer werden (200ms = 60grad)
  float millisekFuerEinenGrad = 3.33;
  float millisek = winkel * millisekFuerEinenGrad;
  motor(Motor_links_A_Pin, Motor_links_B_Pin, true, 200);
  motor(Motor_rechts_A_Pin, Motor_rechts_B_Pin, false, 200);

  delay(millisek);

  motor(Motor_links_A_Pin, Motor_links_B_Pin, true, 0);
  motor(Motor_rechts_A_Pin, Motor_rechts_B_Pin, true, 0);
}

void fahren() {
  motor(Motor_links_A_Pin, Motor_links_B_Pin, true, 200);
  motor(Motor_rechts_A_Pin, Motor_rechts_B_Pin, true, 200);
}

void motor(int pinA, int pinB, bool richtungVR, int temp) {     // true == vorwerts
  if (richtungVR) { PWM_analogWrite(pinA, temp);  PWM_analogWrite(pinB, 0); }
  else        { PWM_analogWrite(pinA, 0);  PWM_analogWrite(pinB, temp); }
}
