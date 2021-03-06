#pragma once

#include "arduino.h"

#ifndef CV_MOTOR_CONTROLLER_H
#define CV_MOTOR_CONTROLLER_H

namespace CheapVentilator
{
	enum ECVState {
		DISABLE,
		FORWARD,
		BACK,
		IDLE
	};

	typedef void(*MotorControllerMoveHandler)(unsigned short, boolean);
	typedef void(*MotorControllerStopHandler)(void);
	typedef void(*MotorControllerChangeStateHandler)(ECVState);

	class MotorController
	{
		unsigned short switchPin;

		const unsigned short minSpeed = 1;
		const unsigned short maxSpeed = 255;
		const unsigned short backSpeed = 127;

		const unsigned short minForward = 1;
		const unsigned short maxForward = 1200;

		const unsigned short minIdleTime = 0;
		const unsigned short maxIdletime = 8000;

		unsigned short pumpingSpeed;
		unsigned short pumpingForward;

		unsigned int idleTime;
		unsigned long stopTime;

		ECVState state;

		MotorControllerMoveHandler onMoveHandler;
		MotorControllerStopHandler onStopHandler;
		MotorControllerChangeStateHandler onChangeStateHandler;

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
		MotorController(const unsigned short switchPin);
		~MotorController();

		void begin();
		void restart();
		void update();
		void stop();

		void onMove(MotorControllerMoveHandler handler) { onMoveHandler = handler; }
		void onStop(MotorControllerStopHandler handler) { onStopHandler = handler; }
		void onChangeState(MotorControllerChangeStateHandler handler) { onChangeStateHandler = handler; }

		void setSpeed(const unsigned short speed) { this->pumpingSpeed = constrain(speed, minSpeed, maxSpeed); }
		const unsigned short getSpeed() { return this->pumpingSpeed; }

		void setForward(const unsigned short forward) { this->pumpingForward = constrain(forward, minForward, maxForward); }
		const unsigned short getForward() { return this->pumpingForward; }

		void setIdleTime(const unsigned int milliseconds) { this->idleTime = constrain(milliseconds, minIdleTime, maxIdletime); }
		const unsigned int getIdleTime() { return this->idleTime; }

		char const* getStateName(ECVState);
		char const* getStateName() { return getStateName(this->state); }
	};
}

#endif
