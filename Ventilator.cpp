#include "Ventilator.h"

Ventilator::Ventilator(unsigned short lEN, unsigned short rEN, unsigned short lPWM, unsigned short rPWM, unsigned short switchPin)
{
	this->switchPin = switchPin;

	this->state = DISABLED;
	this->idleTime = 5000;
	
	this->pumpingSpeed = 100;
	this->pumpingForwardDistance = 700;
	
	this->prepareSpeed = 50;
	this->prepareForwardDistance = 100;

	this->minSpeed = 50;
	this->maxSpeed = 255;

	this->minDistance = 20;
	this->maxDistance = 900;

	this->motorController = new BTS7960(lEN, rEN, lPWM, rPWM);
}

void Ventilator::turnMotor(unsigned int distance, unsigned short speed, bool right)
{
	float speedRating = (float) maxSpeed / speed;
	float duration = distance * speedRating;

	motorController->Enable();

	if (right)
		motorController->TurnRight(speed);
	else 
		motorController->TurnLeft(speed);

	myDelay(duration);
}

void Ventilator::moveForward(unsigned int distance, unsigned short speed)
{
	state = FORWARD;
	turnMotor(constrain(distance, minDistance, maxDistance), constrain(speed, minSpeed, maxSpeed), true);

	if (state == FORWARD) 
		moveBack();
}

void Ventilator::moveBack(unsigned int distance, unsigned short speed)
{
	state = BACK;
	turnMotor(distance, speed, false);

	if (state == BACK)
		idle(idleTime);
}

void Ventilator::moveBack()
{
	 moveBack(3000, pumpingSpeed);
}

void Ventilator::idle(unsigned int waitTime)
{
	state = IDLE;
	motorController->Stop();

	myDelay(waitTime);

	if (state == IDLE)
		moveForward(pumpingForwardDistance, pumpingSpeed);
}

void Ventilator::begin()
{
	pinMode(switchPin, INPUT);
	restart();
}

void Ventilator::restart()
{
	if (state == FORWARD || state == BACK)
		idle(100);

	moveForward(prepareForwardDistance, prepareSpeed);
}

void Ventilator::disable()
{
	state = DISABLED;
	motorController->Stop();
}

void Ventilator::myDelay(unsigned long duration)
{  
	unsigned long start = millis();

	while (millis() - start <= duration)
	{
		if (state == BACK && digitalRead(switchPin) == HIGH)
		{
			idle(idleTime);
			break;
		}
	}
}