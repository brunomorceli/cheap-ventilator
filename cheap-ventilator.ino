#include "BTS7960.h"
#include "./Ventilator.h"

#define L_EN 8
#define R_EN 9
#define L_PWM 10
#define R_PWM 11
#define SWITCH_PIN 12

BTS7960 motorController(L_EN, R_EN, L_PWM, R_PWM);

Ventilator ventilator(SWITCH_PIN);
void setup() 
{
  Serial.begin(9600);
  ventilator.begin();

  ventilator.onStop([]() {
    motorController.Stop();
  });
   
  ventilator.onMove([](unsigned short speed, boolean clockwise) {
    motorController.Enable();
    if (clockwise)
      motorController.TurnRight(speed);
     else
     motorController.TurnLeft(speed);
  });

 
}

void loop() 
{
  ventilator.update();
}
