#include "arduino.h"

#pragma once

#ifndef CHEAP_VENTILATOR_H
#define CHEAP_VENTILATOR_H

enum ECVState {
	DISABLE,
	FORWARD,
	BACK,
	IDLE
};

typedef void(*MoveHandler)(unsigned short, boolean);
typedef void(*StopHandler)(void);
typedef void(*ChangeStateHandler)(ECVState);

class CheapVentilator
{
	unsigned short switchPin;

	const unsigned short minSpeed = 1;
	const unsigned short maxSpeed = 255;
	const unsigned short backSpeed = 127;

	const unsigned short minForward = 1;
	const unsigned short maxForward = 1200;

	unsigned short pumpingSpeed;
	unsigned short pumpingForward;

	unsigned int idleTime;
	unsigned long stopTime;

	ECVState state;

	MoveHandler onMoveHandler;
	StopHandler onStopHandler;
	ChangeStateHandler onChangeStateHandler;

	void setState(const ECVState state);
	void nextState();

	unsigned long calculateDuration(
		const unsigned short forward,
		const unsigned short speed
	);

	void move(
		const unsigned int forward,
		const unsigned short
		speed,
		const bool clockwise
	);

	void moveForward(
		const unsigned int forward, 
		const unsigned short speed
	);

	void moveBack(
		const unsigned int forward,
		const unsigned short speed
	);

	void moveBack();

public:
	CheapVentilator(const unsigned short switchPin);
	~CheapVentilator();

	void begin();
	void restart();
	void update();
	void stop();

	void onMove(MoveHandler handler) { onMoveHandler = handler; }
	void onStop(StopHandler handler) { onStopHandler = handler; }
	void onChangeState(ChangeStateHandler handler) { onChangeStateHandler = handler; }

	void setSpeed(const unsigned short speed) { this->pumpingSpeed = speed; }
	const unsigned short getSpeed() { return this->pumpingSpeed; }

	void setForward(const unsigned short forward) { this->pumpingForward = forward; }
	const unsigned short getForward() { return this->pumpingForward; }

	void setIdleTime(const unsigned int milliseconds) { this->idleTime = milliseconds; }
	const unsigned int getIdleTime() { return this->idleTime; }

	char const* getStateName(ECVState);
	char const* getStateName() { return getStateName(this->state); }
};

#endif
