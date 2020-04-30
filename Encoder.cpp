#include "Encoder.h"

namespace CheapVentilator
{
	Encoder::Encoder(const unsigned short CLKPin, const unsigned short DTPin, const unsigned short SWPin)
	{
    this->CLKPin = CLKPin;
    this->DTPin = DTPin;
    this->SWPin = SWPin;

    this->delayTime = 100;
    this->nextActionTime = 0;
    this->clockwise = true;
    this->click = false;

    this->onNextHandler = NULL;
    this->onPreviewHandler = NULL;
    this->onClickHandler = NULL;

    pinMode (this->CLKPin, INPUT);
    pinMode (this->DTPin,  INPUT);
    pinMode (this->SWPin, INPUT_PULLUP);
	}

  Encoder::~Encoder() {}

  void Encoder::setNextAction(unsigned long time)
  {
    nextActionTime = millis() + time;
  }

  void Encoder::triggerOnNextEvent()
  {
    setNextAction(100);
    if (onNextHandler != NULL)
      onNextHandler();
  }

  void Encoder::triggerOnPreview()
  {
    setNextAction(delayTime);
    if (onPreviewHandler != NULL)
      onPreviewHandler();
  }

  void Encoder::triggerOnClick()
  {
    setNextAction(delayTime);
    if (onClickHandler != NULL)
      onClickHandler();
  }

  void Encoder::update()
  {
    unsigned long now = millis();
    unsigned int currentCKL = digitalRead(CLKPin);
    unsigned int currentDT = digitalRead(DTPin);
    bool currentClick = digitalRead(SWPin) == LOW;

    if (now < nextActionTime)
      return;

    // check the switch status (button)
    if(currentClick)
    {
      click = currentClick;
      triggerOnClick();
    }

    // no direct change.
    if (currentCKL != currentDT)
    {
      clockwise = currentCKL;
      if (currentCKL)
        triggerOnNextEvent();
      else
        triggerOnPreview();
    }
  }
}