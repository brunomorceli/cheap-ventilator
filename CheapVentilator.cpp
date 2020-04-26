#include "CheapVentilator.h"

CheapVentilator::CheapVentilator(const unsigned short switchPin)
{
	this->switchPin = switchPin;

	this->pumpingSpeed = 127;
	this->pumpingForward = 700;

	this->idleTime = 3000;
	this->stopTime = 0.0f;

	this->state = DISABLE;

	onMoveHandler = NULL;
	onStopHandler = NULL;
	onChangeStateHandler = NULL;
}

CheapVentilator::~CheapVentilator()
{
	// void
}

void CheapVentilator::setState(const ECVState state)
{
	if (this->state == state)
		return;
	
	this->state = state;

	if (onChangeStateHandler != NULL)
		onChangeStateHandler(state);

	if (onStopHandler != NULL)
		onStopHandler();

	switch (state)
	{
		case IDLE:
			stopTime = millis() + idleTime;
			break;
		case FORWARD:
			moveForward(pumpingForward, pumpingSpeed);
			break;
		case BACK: 
			moveBack();
			break;
		default:
			break;
	}
}

void CheapVentilator::nextState()
{
	switch (state)
	{
		case IDLE:
			setState(FORWARD);
			break;
		case FORWARD:
			setState(BACK);
			break;
		case BACK:
			setState(IDLE);
			break;
		default:
			break;
	}
}

unsigned long CheapVentilator::calculateDuration(const unsigned short forward, const unsigned short speed)
{
	float ratio = (float)this->maxSpeed / speed;
	return (forward * ratio);
}

void CheapVentilator::move(const unsigned int forward, const unsigned short speed, const bool clockwise)
{
	stopTime = millis() + calculateDuration(
		constrain(forward, this->minForward, this->maxForward),
		constrain(speed, this->minSpeed, this->maxSpeed)
	);

	if (onMoveHandler != NULL && onStopHandler != NULL)
		onMoveHandler(speed, clockwise);
}

void CheapVentilator::moveForward(const unsigned int forward, const unsigned short speed)
{
	move(forward, speed, true);
}

void CheapVentilator::moveBack(const unsigned int forward, const unsigned short speed)
{
	move(forward, speed, false);
}

void CheapVentilator::moveBack()
{
	 moveBack(this->maxForward * 2, this->backSpeed);
}

void CheapVentilator::begin()
{
	pinMode(switchPin, INPUT);
	restart();
}

void CheapVentilator::restart()
{
	setState(BACK);
}

void CheapVentilator::stop()
{
	state = DISABLE;
	moveBack();

	if (onStopHandler != NULL)
		onStopHandler();

	if (onChangeStateHandler != NULL)
		onChangeStateHandler(state);
}

void CheapVentilator::update()
{
	bool switchPushed = digitalRead(switchPin) == HIGH;
	if ((state == BACK && switchPushed) || (stopTime > 0 && stopTime < millis()))
		nextState();
}

char const* CheapVentilator::getStateName(ECVState)
{
	switch (state)
	{
		case DISABLE:
			return "DISABLE";
		case IDLE:
			return "IDLE";
		case FORWARD:
			return "FORWARD";
			break;
		case BACK:
			return "BACK";
			break;
		default:
			return "UNKNOWN";
			break;
	}
}
