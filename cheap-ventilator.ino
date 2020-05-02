#include "BTS7960.h"
#include "./MotorController.h"
#include "./Encoder.h"
#include "./MenuItem.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define L_EN 8
#define R_EN 9
#define L_PWM 10
#define R_PWM 11
#define SWITCH_PIN 12

using namespace CheapVentilator;


// =============================================
//                      MENU
// =============================================

void printOptions(MenuItem* menuItem, Adafruit_SSD1306 &display)
{
  display.clearDisplay();

  MenuRenderItem item = menuItem->getSelectedItem()->getRender();

  display.setCursor(0, 0);
  display.print(item.title);

  display.setCursor(0, 10);

  String label = item.amountLabel;
  
  if (item.editing)
    label = "set: " + label;

  display.print(label);
  display.display();
}

MenuItem menu("");
BTS7960 dcMotorController(L_EN, R_EN, L_PWM, R_PWM);
Encoder encoder(3,4,5);

Adafruit_SSD1306 display = Adafruit_SSD1306();

MotorController cvMotorController(SWITCH_PIN);
void setup() 
{
  Serial.begin(9600);

  // display
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setTextWrap(true);
  display.clearDisplay();

  // SPEED
  MenuItem* speedItem = new MenuItem("Speed", 1, 100, 50, PERCENT, 10);
  speedItem->onChangeAmount([](float amount) { cvMotorController.setSpeed(amount * 2.5f); });
  menu.addItem(speedItem);

  // PRESSURE
  MenuItem* pressureItem = new MenuItem("Pressure", 1, 100, 60, PERCENT, 10);
  pressureItem->onChangeAmount([](float amount) { cvMotorController.setForward(amount * 9); });
  menu.addItem(pressureItem);

  // IDLE TIME
  MenuItem* idleTimeItem = new MenuItem("Idle Time", 1, 8, 3, RANGE, 1);
  idleTimeItem->onChangeAmount([](float amount) { cvMotorController.setIdleTime(amount * 1000); });
  menu.addItem(idleTimeItem);

  // LANGUAGE
  MenuItem* languageItem = new MenuItem("Language");
  languageItem->addItem(new MenuItem("English"));
  languageItem->addItem(new MenuItem("Portugues"));
  menu.addItem(languageItem);
  

  cvMotorController.onChangeState([](ECVState state) {
    //Serial.println(cvMotorController.getStateName());
  });

  cvMotorController.onStop([]() {
    dcMotorController.Stop();
  });

  cvMotorController.onMove([](unsigned short speed, boolean clockwise) {
    dcMotorController.Enable();
    if (clockwise)
      dcMotorController.TurnRight(speed);
     else
     dcMotorController.TurnLeft(speed);
  });

  cvMotorController.begin();


  encoder.onNext([]() {
    if (menu.getEditing())
      menu.getSelectedItem()->increase();
    else
      menu.selectNextItem();

    printOptions(&menu, display);
  });

  encoder.onPreview([]() {
    if (menu.getEditing())
      menu.getSelectedItem()->decrease();
    else
      menu.selectPreviewItem();

    printOptions(&menu, display);
  });

  encoder.onClick([]() {
    menu.toggleEditing();
    printOptions(&menu, display);
  });
}

void loop() 
{
  encoder.update();
  cvMotorController.update();
}
