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

void drawBar(Adafruit_SSD1306 &display, int VALUE, int yPos, int barHeight=10, int displayWidth=128)
{
  int fillWidth = (int)(((float) (displayWidth-4) / 100.0f) * VALUE);

  display.drawRect(1, yPos, displayWidth - 1, barHeight, WHITE);
  display.fillRect(3, yPos + 2, constrain(fillWidth, 0, displayWidth-4), barHeight-4, WHITE);
}

void drawItem(Adafruit_SSD1306 &display, MenuRenderItem item)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(0, 2);
  display.print(item.title);

  if (item.type == TEXT)
  {
    display.setTextSize(1);
    display.setCursor(0, 12);
    display.print(item.amountLabel);

    display.display();
    return;
  }

  if (!item.editing)
  {
    display.setTextSize(2);
    display.setCursor(0, 12);
    display.print(item.amountLabel);

    display.display();
    return;
  }

  int barHeight = 10;
  int barWidth = (item.amount * 100) / item.maxVal;
  drawBar(display, barWidth, 12, barHeight);

  display.setTextSize(1);
  display.setCursor(10, 14 + barHeight);
  display.print(item.amountLabel);

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
  MenuItem* speedItem = new MenuItem("Forward Speed", 10, 100, 50, VALUE, 10, "", "%");
  speedItem->onChangeAmount([](float amount) { cvMotorController.setSpeed(amount * 2.5f); });
  menu.addItem(speedItem);

  // FORWARD DISTANCE
  MenuItem* forwardItem = new MenuItem("Forward Distance", 0, 100, 60, VALUE, 10, "", "%");
  forwardItem->onChangeAmount([](float amount) { cvMotorController.setForward(amount * 9); });
  menu.addItem(forwardItem);

  // IDLE TIME
  MenuItem* idleTimeItem = new MenuItem("Idle Time", 0, 8, 3, VALUE, 1, "", " sec");
  idleTimeItem->onChangeAmount([](float amount) { cvMotorController.setIdleTime(amount * 1000); });
  menu.addItem(idleTimeItem);

  // ABOUT
  MenuItem* aboutItem = new MenuItem("Created by:", "Bruno Morceli\r\npirofagista@gmail.com");
  menu.addItem(aboutItem);

  drawItem(display, menu.getSelectedItem()->getRender());
  
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

    drawItem(display, menu.getSelectedItem()->getRender());
  });

  encoder.onPreview([]() {
    if (menu.getEditing())
      menu.getSelectedItem()->decrease();
    else
      menu.selectPreviewItem();

    drawItem(display, menu.getSelectedItem()->getRender());
  });

  encoder.onClick([]() {
    menu.toggleEditing();
    drawItem(display, menu.getSelectedItem()->getRender());
  });
}

void loop() 
{
  encoder.update();
  cvMotorController.update();
}
