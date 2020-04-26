#include "BTS7960.h"
#include "./CheapVentilator.h"

#define L_EN 8
#define R_EN 9
#define L_PWM 10
#define R_PWM 11
#define SWITCH_PIN 12

BTS7960 motorController(L_EN, R_EN, L_PWM, R_PWM);

CheapVentilator cv(SWITCH_PIN);
void setup() 
{
  Serial.begin(9600);

  cv.onChangeState([](ECVState state) {
    Serial.println(cv.getStateName());
  });

  cv.onStop([]() {
    motorController.Stop();
  });

  cv.onMove([](unsigned short speed, boolean clockwise) {
    motorController.Enable();
    if (clockwise)
      motorController.TurnRight(speed);
     else
     motorController.TurnLeft(speed);
  });

  cv.begin();
}

void loop() 
{
  cv.update();
}
