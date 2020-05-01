#include "Encoder.h"

namespace CheapVentilator
{
  Encoder::Encoder(const unsigned short outputA, const unsigned short outputB, const unsigned short switchOutput)
  {
    this->outputA = outputA;
    this->outputB = outputB;
    this->switchOutput = switchOutput;

    this->delayTime = 200;
    this->nextActionTime = 0;

    this->onNextHandler = NULL;
    this->onPreviewHandler = NULL;
    this->onClickHandler = NULL;

    pinMode (this->outputA, INPUT);
    pinMode (this->outputB,  INPUT);
    pinMode (this->switchOutput, INPUT_PULLUP);

    this->aLastState = digitalRead(outputA);
  }

  Encoder::~Encoder() {}

  void Encoder::setNextAction(unsigned long time)
  {
    nextActionTime = millis() + time;
  }

  void Encoder::triggerOnNextEvent()
  {
    setNextAction(delayTime);
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
    setNextAction(500);
    if (onClickHandler != NULL)
      onClickHandler();
  }

  void Encoder::update()
  {
    aState = digitalRead(outputA);
    unsigned long now = millis();

    if (now < nextActionTime)
    {
      aLastState = aState;
      return;
    }

    if (switchOutput > 0 && digitalRead(switchOutput) == LOW)
    {
      if (!switchLastState)
        triggerOnClick();

      switchLastState = true;
    }
    else
      switchLastState = false;

    if (aState != aLastState)
    {
      if (digitalRead(outputB) != aState)
        triggerOnNextEvent();
      else
        triggerOnPreview();
    }
    
    aLastState = aState;
  }
}