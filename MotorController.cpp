#include "MotorController.h"

namespace CheapVentilator
{
	MotorController::MotorController(const unsigned short switchPin)
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

	MotorController::~MotorController()
	{
		// void
	}

	void MotorController::setState(const ECVState state)
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

	void MotorController::nextState()
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

	unsigned long MotorController::calculateDuration(const unsigned short forward, const unsigned short speed)
	{
		float ratio = (float)this->maxSpeed / speed;
		return (forward * ratio);
	}

	void MotorController::move(const unsigned int forward, const unsigned short speed, const bool clockwise)
	{
		stopTime = millis() + calculateDuration(
			constrain(forward, this->minForward, this->maxForward),
			constrain(speed, this->minSpeed, this->maxSpeed)
		);

		if (onMoveHandler != NULL && onStopHandler != NULL)
			onMoveHandler(speed, clockwise);
	}

	void MotorController::moveForward(const unsigned int forward, const unsigned short speed)
	{
		move(forward, speed, true);
	}

	void MotorController::moveBack(const unsigned int forward, const unsigned short speed)
	{
		move(forward, speed, false);
	}

	void MotorController::moveBack()
	{
		moveBack(this->maxForward * 2, this->backSpeed);
	}

	void MotorController::begin()
	{
		pinMode(switchPin, INPUT_PULLUP);
		restart();
	}

	void MotorController::restart()
	{
		stopTime = 1;
		state = FORWARD;
	}

	void MotorController::stop()
	{
		state = DISABLE;
		moveBack();

		if (onStopHandler != NULL)
			onStopHandler();

		if (onChangeStateHandler != NULL)
			onChangeStateHandler(state);
	}

	void MotorController::update()
	{
		if (state == DISABLE)
			return;

		if (stopTime < millis())
		{
			nextState();
			return;
		}
		
		int switchPushed = digitalRead(switchPin) == LOW;
		if (state == BACK && switchPushed)
			nextState();
	}

	char const* MotorController::getStateName(ECVState)
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
}
