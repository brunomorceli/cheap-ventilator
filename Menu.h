/*#pragma once

#include <arduino.h>

#ifndef CV_MENU_H
#define CV_MENU_H

#define MENU_MAX_LANGUAGES 3
#define MENU_MAX_ITEMS 6
#define MENU_MAX_OPTIONS 10
#define MENU_MAX_LABELS 3

namespace CheapVentilator
{
  enum eMenuLanguage
  {
    ENGLISH,
    PORTUGUESE,
    SPANISH
  };

  enum eMenuItemType
  {
    CONFIRM,
    SELECT,
    TEXT
  };

  enum eMenuItemStatus
  {
    MIS_SPEED,
    MIS_FORWARD,
    MIS_IDLE_TIME,
    MIS_LANGUAGE,
    MIS_RESET,
    MIS_NONE
  };

  enum eMenuOptionPosition
  {
    FIRST,
    MIDDLE,
    LAST
  };

  struct MenuOption {
    String label;
    unsigned short value;
  };

  struct MenuItem {
    eMenuItemStatus status;
    eMenuItemType type;
    String* label = new String[MENU_MAX_LABELS];
    MenuOption* options = new MenuOption[MENU_MAX_OPTIONS];
    unsigned short optionCount;
    unsigned short selectedOption;
    unsigned short defaultOption;

    unsigned short getProgress() { return ((selectedOption + 1) * 100) / optionCount; }
    MenuOption getSelectedOption() { return options[selectedOption]; }

    eMenuOptionPosition getPosition()
    {
      if (selectedOption == 0)
        return FIRST;
      
      if (selectedOption < (optionCount - 1))
        return MIDDLE;
      
      return LAST;
    }
  };

  struct MenuItemRender
  {
    public:
    eMenuItemStatus status;
    eMenuItemType type;
    eMenuOptionPosition position;
    boolean editing;
    String label;
    String optionLabel;
    unsigned short optionValue;
    unsigned short optionProgress;
  };

  typedef void(*MenuChangeHandler)(MenuItemRender);

  //==============================================================================
  // MENU
  //==============================================================================

	class Menu
	{
    eMenuLanguage selectedLang;
    MenuItem* items = new MenuItem[MENU_MAX_ITEMS];

    unsigned short selectedItem;
    boolean editing;

    MenuChangeHandler changeHandler;

    void emitOnChange();

    void nextOption();
    void previewOption();

    void nextItem();
    void previewItem();

	public:
		Menu(eMenuLanguage language=ENGLISH);
    ~Menu();
    void next();
    void preview();

    boolean getEdit() { return editing; }
    void setEdit(boolean stat) { editing = stat; }
    void toggleEdit() { editing = !editing; }

    MenuItemRender getCurrentItem();
 
    void onChange(MenuChangeHandler handler) { changeHandler = handler; }

    void begin() { emitOnChange(); }
	};
}

#endif
*/