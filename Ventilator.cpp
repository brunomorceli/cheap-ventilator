#include "Ventilator.h"

Ventilator::Ventilator(const unsigned short switchPin)
{
	this->switchPin = switchPin;

	this->pumpingSpeed = 127;
	this->pumpingForward = 600;

	this->idleTime = 4000;
	this->stopTime = 0.0f;

	this->state = DISABLE;

	onMoveHandler = NULL;
	onStopHandler = NULL;
	onChangeStateHandler = NULL;
}

Ventilator::~Ventilator()
{
	// void
}

void Ventilator::setState(const EMovementState state)
{
	if (this->state != state && onChangeStateHandler != NULL)
		onChangeStateHandler(state);

	this->state = state;

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

void Ventilator::nextState()
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

unsigned long Ventilator::calculateDuration(const unsigned short forward, const unsigned short speed)
{
	return (unsigned long) (forward * (float)(this->maxSpeed / speed));
}

void Ventilator::move(const unsigned int forward, const unsigned short speed, const bool clockwise)
{
	stopTime = millis() + calculateDuration(
		constrain(forward, this->minForward, this->maxForward),
		constrain(speed, this->minSpeed, this->maxSpeed)
	);

	if (onMoveHandler != NULL && onStopHandler != NULL)
		onMoveHandler(speed, clockwise);
}

void Ventilator::moveForward(const unsigned int forward, const unsigned short speed)
{
	move(forward, speed, true);
}

void Ventilator::moveBack(const unsigned int forward, const unsigned short speed)
{
	move(forward, speed, false);
}

void Ventilator::moveBack()
{
	 moveBack(this->maxForward * 2, pumpingSpeed);
}

void Ventilator::begin()
{
	pinMode(switchPin, INPUT);
	restart();
}

void Ventilator::restart()
{
	stopTime = 0.0f;
	setState(FORWARD);
}

void Ventilator::stop()
{
	state = DISABLE;
	stopTime = 0.0f;

	if (onStopHandler != NULL)
		onStopHandler();

	if (onChangeStateHandler != NULL)
		onChangeStateHandler(state);
}

void Ventilator::update()
{
	bool switchPushed = digitalRead(switchPin) == HIGH;
	if ((state == BACK && switchPushed) || (stopTime > 0 && stopTime < millis()))
		nextState();
}
