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
    float minVal;
    float maxVal;
    float amount;
    float amountStep;
    String amountLabel;
    boolean selected;
    boolean editing;
  };

  typedef void(*MenuChangeAmountHandler)(float);

	class MenuItem
	{
    MenuItem* parent;
    eMenuItemType type;

    String title;
    float minVal;
    float maxVal;
    float amount;
    float amountStep;

    Vector<MenuItem*> items;
    unsigned short selectedItem;
    boolean selected;
    boolean editing;

    MenuChangeAmountHandler changeAmountHandler;

    void emitChangeAmount();

	public:
		MenuItem(String title);

    MenuItem(
      String title,
      const float minVal,
      const float maxVal,
      const float amount,
      const eMenuItemType type=PERCENT,
      const float amountStep=1
    );

    ~MenuItem();

    MenuItem* getParent() { return parent; }
    void setParent(MenuItem* parent) { this->parent = parent; }
    eMenuItemType getType() { return type; }
    String getTitle() { return title; }
    float getMin() { return minVal; }
    float getMax() { return maxVal; }
    float getAmount() { return amount; }
    float getAmountStep() { return amountStep; }
    String getAmountLabel();
    unsigned short getItemCount() { return items.size(); }

    bool getEditing() { return editing; }
    void setEditing(bool stat) { this->editing = stat; }
    void toggleEditing() { setEditing(!editing); }

    bool getSelected() { return selected; }
    void setSelected(bool stat) { this->selected = stat; }
    void toggleSelected() { setSelected(!selected); }

    void addItem(MenuItem* item);

    float increase(const float val);
    float increase() { return increase(amountStep); }
    float decrease(const float val);
    float decrease() { return decrease(amountStep); }

    void selectNextItem();
    void selectPreviewItem();
    MenuItem* getSelectedItem() { return items[selectedItem]; }

    MenuRenderItem getRender();
    void getRenderItems(Vector<MenuRenderItem> &result);

    void onChangeAmount(MenuChangeAmountHandler handler) { changeAmountHandler = handler; }
	};
}

#endif
