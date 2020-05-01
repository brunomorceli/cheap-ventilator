#include "BTS7960.h"
#include "./MotorController.h"
#include "./Encoder.h"
#include "./MenuItem.h"

#define L_EN 8
#define R_EN 9
#define L_PWM 10
#define R_PWM 11
#define SWITCH_PIN 12

#define CONTROLLER_PIN A0

using namespace CheapVentilator;


// =============================================
//                      MENU
// =============================================

void printOptions(MenuItem* menuItem)
{
  Vector<MenuRenderItem> renderList;
  menuItem->getRenderItems(renderList);

  for (int i = 0; i < renderList.size(); i++)
  {
    if (renderList[i].selected)
      Serial.print("> ");
    Serial.println(renderList[i].title);
  }
}

MenuItem rootItem("root");
BTS7960 dcMotorController(L_EN, R_EN, L_PWM, R_PWM);
Encoder encoder(3,4,5);

MotorController cvMotorController(SWITCH_PIN);
void setup() 
{
  Serial.begin(9600);

  rootItem.addItem(new MenuItem("Speed", 0, 255, 127, PERCENT, 1));
  rootItem.addItem(new MenuItem("pressure", 0, 900, 700, PERCENT, 50));
  rootItem.addItem(new MenuItem("Idle Time", 0, 1, 8, RANGE, 1));
  
  MenuItem* languageItem = new MenuItem("Language");
  
  languageItem->addItem(new MenuItem("English"));
  languageItem->addItem(new MenuItem("Portugues"));
  
  rootItem.addItem(languageItem);
  

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
    //Serial.println("Next");
    rootItem.selectNextItem();
    printOptions(&rootItem);
  });

  encoder.onPreview([]() {
    //Serial.println("Preview");
    rootItem.selectPreviewItem();
    printOptions(&rootItem);
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
