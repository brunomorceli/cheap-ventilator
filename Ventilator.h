#include "arduino.h"

#pragma once

#ifndef VENTILATOR_H
#define VENTILATOR_H

enum EMovementState {
	DISABLE,
	FORWARD,
	BACK,
	IDLE
};

typedef void(*MoveHandler)(unsigned short, boolean);
typedef void(*StopHandler)(void);
typedef void(*ChangeStateHandler)(EMovementState);

class Ventilator
{
	unsigned short switchPin;

	const unsigned short minSpeed = 50;
	const unsigned short maxSpeed = 255;

	const unsigned short minForward = 20;
	const unsigned short maxForward = 1200;

	unsigned short pumpingSpeed;
	unsigned short pumpingForward;

	unsigned int idleTime;
	unsigned long stopTime;

	EMovementState state;

	MoveHandler onMoveHandler;
	StopHandler onStopHandler;
	ChangeStateHandler onChangeStateHandler;

	void setState(const EMovementState state);
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
	Ventilator(const unsigned short switchPin);
	~Ventilator();

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
};

#endif
