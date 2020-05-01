#pragma once

#include <arduino.h>
#include <Vector.h>

#ifndef CV_MENU_ITEM_H
#define CV_MENU_ITEM_H

namespace CheapVentilator
{
  enum eMenuItemType
  {
    RANGE,
    PERCENT,
    SELECT
  };

  struct MenuRenderItem {
    String title;
    int min;
    int max;
    int amount;
    int amountStep;
    String amountLabel;
    boolean selected;
  };

	class MenuItem
	{
    MenuItem* parent;
    eMenuItemType type;

    String title;
    int min;
    int max;
    int amount;
    int amountStep;

    Vector<MenuItem*> items;
    short selectedItem;

	public:
		MenuItem(String title);

    MenuItem(
      String title,
      const int min,
      const int max,
      const int amount,
      const eMenuItemType type=PERCENT,
      const unsigned int amountStep=1
    );

    ~MenuItem();

    MenuItem* getParent() { return parent; }
    void setParent(MenuItem* parent) { this->parent = parent; }
    eMenuItemType getType() { return type; }
    String getTitle() { return title; }
    int getMin() { return min; }
    int getMax() { return max; }
    int getAmount() { return amount; }
    int getAmountStep() { return amountStep; }
    String getAmountLabel();
    unsigned short getItemCount() { return items.size(); }

    void addItem(MenuItem* item, boolean selected=false);

    void increase(const unsigned int val) { amount = constrain(amount + val, min, max); }
    void increase() { increase(amountStep); }
    void decrease(const unsigned int val) { amount = constrain(amount - val, min, max); }
    void decrease() { decrease(amountStep); }

    void selectNextItem();
    void selectPreviewItem();
    MenuItem* getSelectedItem() { return items[selectedItem]; }

    MenuRenderItem getRender(bool selected);
    MenuRenderItem getRender() { return getRender(false); }
    void getRenderItems(Vector<MenuRenderItem> &result);
	};
}

#endif
