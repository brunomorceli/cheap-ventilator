#include "arduino.h"
#include "BTS7960.h"

#pragma once

#ifndef VENTILATOR_H
#define VENTILATOR_H

enum EVentilatorState {
	DISABLED,
	IDLE,
	FORWARD,
	BACK
};

class Ventilator
{
private:
	unsigned short switchPin;

	EVentilatorState state;
	unsigned int idleTime;

	unsigned short pumpingSpeed;
	unsigned int pumpingForwardDistance;

	unsigned short prepareSpeed;
	unsigned int prepareForwardDistance;

	unsigned int minSpeed;
	unsigned int maxSpeed;
	unsigned int minDistance;
	unsigned int maxDistance;

	BTS7960 *motorController;

	void turnMotor(unsigned int distance, unsigned short speed, bool right);

	void moveForward(unsigned int distance, unsigned short speed);
	void moveBack(unsigned int distance, unsigned short speed);
	void moveBack();

	void idle(unsigned int waitTime);

	void myDelay(unsigned long duration);

public:
	Ventilator(unsigned short lEN, unsigned short rEN, unsigned short lPWM, unsigned short rPWM, unsigned short switchPin);

	void setPumpingSpeed(unsigned short speed);
	unsigned short getPumpingSpeed() { return pumpingSpeed; }

	void begin();
	void restart();
	void disable();
};

#endif
