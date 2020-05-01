#include "MenuItem.h"

namespace CheapVentilator
{
  MenuItem::MenuItem(String title)
  {
    this->parent = NULL;
    this->title = title;
    this->type = SELECT;

    this->min = 0;
    this->max = 0;
    this->amount = 0;
    this->amountStep = 0;
    this->selectedItem = -1;
  }

  MenuItem::MenuItem(
    String title,
    const int min,
    const int max,
    const int amount,
    const eMenuItemType type,
    const unsigned int amountStep
  )
  {
    this->parent = NULL;
    this->title = title;
    this->type = type;

    this->min = min;
    this->max = max;
    this->amount = constrain(amount, min, max);
    this->amountStep = amountStep;
  }

  MenuItem::~MenuItem(void) {}

  String  MenuItem::getAmountLabel()
  {
    String result = "";

    if (type == RANGE)
    {
      result += String(amount);
      result += " / ";
      result += String(max);

      return result;
    }

    if (type == PERCENT)
    {
      result += String((amount * 100) / max);
      result += "%";
    }

    return result;
  }

  void MenuItem::addItem(MenuItem* item, boolean selected)
  {
    if (type != SELECT)
      return;

    item->setParent(this);
    items.push_back(item);

    if (selected || items.size() == 1)
      selectedItem = items.size() - 1;
  }

  void MenuItem::selectNextItem()
  {
    selectedItem = constrain(selectedItem - 1, 0, items.size()-1);
  }

  void MenuItem::selectPreviewItem()
  {
    selectedItem = constrain(selectedItem + 1, 0, items.size()-1);
  }

  MenuRenderItem MenuItem::getRender(bool selected)
  {
    MenuRenderItem result{
      this->title,
      this->min,
      this->max,
      this->amount,
      this->amountStep,
      this->getAmountLabel(),
      selected
    };

    return result;
  }

  void MenuItem::getRenderItems(Vector<MenuRenderItem> &result)
  {
    for (int i = 0; i < items.size(); i++)   
      result.push_back(items[i]->getRender(this->selectedItem == i));
  }
}