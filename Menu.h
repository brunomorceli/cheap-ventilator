#pragma once

#include "arduino.h"

#ifndef CV_MENU_H
#define CV_MENU_H

namespace CheapVentilator
{
  enum ECVMenuState
  {
    BROWSING,
    EDITING
  };

  enum EVMenuOption
  {
    SPEED,
    FORWARD_DISTANCE,
    IDLE_TIME,
    LANGUAGE
  };

  enum EVMenuValueType
  {
    RANGE,
    OPTIONS,
    PERCENT
  };

	typedef void(*ChangeStateHandler)(ECVMenuState);
	typedef void(*ChangeOption)(ECVMenuEditStatus, float);

  struct MenuOption
  {
    String title;
    EVMenuOption option;
    EVMenuValueType type;
    unsigned short min;
    unsigned short max;
    unsigned short amount;
    unsigned short step;
    String[] options;
  };
  
	class Menu
	{
		ECVMenuState state;
  
	public:
		Menu();
    ~Menu(void);
	};
}

#endif
