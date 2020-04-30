#pragma once

#include "arduino.h"

#ifndef CV_ENCODER_H
#define CV_ENCODER_H

namespace CheapVentilator
{
	typedef void(*NextHandler)(void);
  typedef void(*PreviewHandler)(void);
	typedef void(*ClickHandler)(void);

	class Encoder
	{
  
    unsigned short CLKPin;
    unsigned short DTPin;
    unsigned short SWPin;

    unsigned long delayTime;
    unsigned long nextActionTime;
    boolean clockwise;
    boolean click;

    NextHandler onNextHandler;
    PreviewHandler onPreviewHandler;
    ClickHandler onClickHandler;


    void setNextAction(unsigned long time);
    void triggerOnNextEvent();
    void triggerOnPreview();
    void triggerOnClick();
 
	public:
		Encoder(const unsigned short CLKPin, const unsigned short DTPin, const unsigned short SWPin);
    ~Encoder(void);

    void onNext(NextHandler handler) { onNextHandler = handler; };
    void onPreview(PreviewHandler handler) { onPreviewHandler = handler; }
    void onClick(ClickHandler handler) { onClickHandler = handler; };

    void setDelay(unsigned long time) { this->delayTime = time; }

    void update();
	};
}

#endif
