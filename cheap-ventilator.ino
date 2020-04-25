#include "./Ventilator.h"

#define L_EN 8
#define R_EN 9
#define L_PWM 10
#define R_PWM 11
#define SWITCH_PIN 12

Ventilator ventilator(L_EN, R_EN, L_PWM, R_PWM, SWITCH_PIN);
void setup() 
{
  Serial.begin(9600);
  ventilator.begin();
}

void loop() 
{
}
