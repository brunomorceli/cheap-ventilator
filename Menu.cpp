/*#include "Menu.h"

namespace CheapVentilator
{
  Menu::Menu(eMenuLanguage language)
  {
    selectedLang = language;
    selectedItem = 0;
    editing = false;



    // SPEED
    // How fast the arm would forward.
    items[0] = MenuItem{};
    items[0].status = MIS_SPEED;
    items[0].type = SELECT;
    items[0].label[0] = "Speed";
    items[0].label[1] = "Velocidade";
    items[0].label[2] = "Velocidad";

    items[0].options[0] = MenuOption{"10%", 10};
    items[0].options[1] = MenuOption{"20%", 20};
    items[0].options[2] = MenuOption{"30%", 30};
    items[0].options[3] = MenuOption{"40%", 40};
    items[0].options[4] = MenuOption{"50%", 50};
    items[0].options[5] = MenuOption{"60%", 60};
    items[0].options[6] = MenuOption{"70%", 70};
    items[0].options[7] = MenuOption{"80%", 80};
    items[0].options[8] = MenuOption{"90%", 90};
    items[0].options[9] = MenuOption{"100%", 100};
    items[0].optionCount = 10;
    items[0].selectedOption = 4;
    items[0].defaultOption = 4;

    // ARM PRESSURE
    // How far the arm would forward
    items[1] = MenuItem {
      MIS_FORWARD,
      SELECT,
      {
        "Arm Pressure",
        "Pressao do Braco",
        "Presion del Brazo"
      },
      {
        {"10%", 10},
        {"20%", 20},
        {"30%", 30},
        {"40%", 40},
        {"50%", 50},
        {"60%", 60},
        {"70%", 70},
        {"80%", 80},
        {"90%", 90},
        {"100%", 100}
      },
      10,
      6,
      6
    };

    // IDLE TIME
    // How much time that the ventilator would wait until a new pumping.
    items[2] = MenuItem {
      MIS_IDLE_TIME,
      SELECT,
      new String[3] {
        "Waiting Time",
        "Tempo de Espera",
        "Tiempo de Espera"
      },
      new MenuOption[8] {
        {"1s", 1},
        {"2s", 2},
        {"3s", 3},
        {"4s", 4},
        {"5s", 5},
        {"6s", 6},
        {"7s", 7},
        {"8s", 8}
      },
      8,
      2,
      2
    };

    // LANGUAGE
    items[3] = MenuItem {
      MIS_LANGUAGE,
      SELECT,
      new String[3] {
        "Language",
        "Idioma",
        "Idioma"
      },
      new MenuOption[3] {
        MenuOption{"English", 0},
        MenuOption{"Portugues", 1},
        MenuOption{"Espanol", 2}
      },
      3,
      selectedLang,
      0
    };

    // RESET
    items[4] = MenuItem {
      MIS_RESET,
      CONFIRM,
      new String[3] {
        "Reset Settings",
        "Redefinir Conf. Padroes",
        "Reiniciar Ajustes"
      },
      new MenuOption[2] {
        MenuOption{"No", 0},
        MenuOption{"Yes", 1}
      },
      2,
      0,
      0
    };

    // ABOUT
    items[5] = MenuItem {
      MIS_NONE,
      TEXT,
      new String[3] {
        "About",
        "Sobre",
        "Acerca de"
      },
      new MenuOption[1] {
        MenuOption{"Created by Bruno Morceli (pirofagista@gmail.com)", 0}
      },
      1,
      0,
      0
    };
  }

  Menu::~Menu() {}

  void Menu::emitOnChange()
  {
    if (changeHandler != NULL)
      changeHandler(getCurrentItem());
  }
  
  void Menu::nextOption()
  {
    MenuItem item = items[selectedItem];
    items[selectedItem].selectedOption = min(item.selectedOption++, item.optionCount - 1);
  }

  void Menu::previewOption()
  {
    MenuItem item = items[selectedItem];
    items[selectedItem].selectedOption = max(item.selectedOption--, 0);
  }

  void Menu::nextItem()
  {
    selectedItem = min(selectedItem++, MENU_MAX_ITEMS-1);
  }

  void Menu::previewItem()
  {
    selectedItem = max(selectedItem--, 0);
  }


  void Menu::next()
  {
    if (editing)
      nextOption();
    else
      nextItem();

    emitOnChange();
  }

  void Menu::preview()
  {
    if (editing)
      previewOption();
    else
      previewItem();

    emitOnChange();
  }

  MenuItemRender Menu::getCurrentItem()
  {
    MenuItem item = items[selectedItem];

    MenuItemRender result {
      item.status,
      item.type,
      item.getPosition(),
      editing,
      item.label[selectedLang],
      item.options[0].label,
      item.options[0].value,
      item.getProgress()
    };

    return result;
  }
}*/
