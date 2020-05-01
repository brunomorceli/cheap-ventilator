#pragma once

#include "arduino.h"

#ifndef CV_ENCODER_H
#define CV_ENCODER_H

namespace CheapVentilator
{
	typedef void(*EncoderNextHandler)(void);
  typedef void(*EncoderPreviewHandler)(void);
	typedef void(*EncoderClickHandler)(void);

	class Encoder
	{
    unsigned short outputA;
    unsigned short outputB;
    unsigned short switchOutput;

    unsigned int aState;
    unsigned int aLastState;
    boolean switchState;
    boolean switchLastState;

    unsigned long delayTime;
    unsigned long nextActionTime;

    EncoderNextHandler onNextHandler;
    EncoderPreviewHandler onPreviewHandler;
    EncoderClickHandler onClickHandler;

    void setNextAction(unsigned long time);
    void triggerOnNextEvent();
    void triggerOnPreview();
    void triggerOnClick();

	public:
		Encoder(
      const unsigned short outputA, 
      const unsigned short outputB, 
      const unsigned short switchOutput=0
    );

    ~Encoder(void);

    void onNext(EncoderNextHandler handler) { onNextHandler = handler; };
    void onPreview(EncoderPreviewHandler handler) { onPreviewHandler = handler; }
    void onClick(EncoderClickHandler handler) { onClickHandler = handler; };

    void setDelay(unsigned long time) { this->delayTime = time; }

    void update();
	};
}

#endif
