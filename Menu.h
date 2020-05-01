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

  enum EVMenuOptionType
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
    EVMenuOptionType type;
    unsigned short min;
    unsigned short max;
    unsigned short amount;
    unsigned short amountStep;
    MenuOption[] options;
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
