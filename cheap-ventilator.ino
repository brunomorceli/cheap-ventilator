#include "BTS7960.h"
#include "./MotorController.h"
#include "./Encoder.h"

#define L_EN 8
#define R_EN 9
#define L_PWM 10
#define R_PWM 11
#define SWITCH_PIN 12

#define CONTROLLER_PIN A0

using namespace CheapVentilator;

BTS7960 dcMotorController(L_EN, R_EN, L_PWM, R_PWM);
Encoder encoder(3,4,5);

MotorController cvMotorController(SWITCH_PIN);
void setup() 
{
  Serial.begin(9600);

  cvMotorController.onChangeState([](ECVState state) {
    Serial.println(cvMotorController.getStateName());
  });

  cvMotorController.onStop([]() {
    dcMotorController.Stop();
  });

  cvMotorController.onMove([](unsigned short speed, boolean clockwise) {
    /*dcMotorController.Enable();
    if (clockwise)
      dcMotorController.TurnRight(speed);
     else
     dcMotorController.TurnLeft(speed);*/
  });

  cvMotorController.begin();


  encoder.onNext([]() {
    Serial.println("Next");
  });

  encoder.onPreview([]() {
    Serial.println("Preview");
  });

  encoder.onClick([]() {
    Serial.println("Click");
  });
}

void loop() 
{
  //int a = analogRead(CONTROLLER_PIN);
  //Serial.println(a);

  encoder.update();
  //cvMotorController.update();
}
