#include "MenuItem.h"

namespace CheapVentilator
{
  MenuItem::MenuItem(String title)
  {
    this->parent = NULL;
    this->title = title;
    this->text = String("");
    this->type = ROOT;

    this->minVal = 0;
    this->maxVal = 0;
    this->amount = 0;
    this->amountStep = 0;
    this->prefix = String("");
    this->suffix = String("");
    this->selected = false;
    this->editing = false;
  }

  MenuItem::MenuItem(String title, String text)
  {
    this->parent = NULL;
    this->title = title;
    this->text = text;
    this->type = TEXT;

    this->minVal = 0;
    this->maxVal = 0;
    this->amount = 0;
    this->prefix = String("");
    this->suffix = String("");
    this->amountStep = 0;
    this->selected = false;
    this->editing = false;
  }

  MenuItem::MenuItem(
    String title,
    const float minVal,
    const float maxVal,
    const float amount,
    const eMenuItemType type,
    const float amountStep,
    String prefix,
    String suffix
  )
  {
    this->parent = NULL;
    this->title = title;
    this->text = String("");
    this->type = type;

    this->minVal = minVal;
    this->maxVal = maxVal;
    this->amount = constrain(amount, minVal, maxVal);
    this->prefix = String(prefix);
    this->suffix = String(suffix);
    this->amountStep = amountStep;
    this->selected = false;
    this->editing = false;
  }

  MenuItem::~MenuItem(void) {}

  void MenuItem::emitChangeAmount()
  {
    if (changeAmountHandler != NULL)
      changeAmountHandler(amount);
  }

  String  MenuItem::getAmountLabel()
  {
    String result = "";

    switch (type)
    {
    case RANGE:
      result += prefix;
      result += String((int)amount);
      result += "/";
      result += String((int)maxVal);
      result += suffix;
      break;
    case VALUE: 
      result += prefix;
      result += (int)amount;
      result += suffix;
    default:
      result += text;
      break;
    }

    return result;
  }

  void MenuItem::addItem(MenuItem* item)
  {
    if (type != ROOT)
      return;

    item->setParent(this);
    item->setSelected(items.size() == 0);

    items.push_back(item);
  }

  float MenuItem::increase(const float val)
  {
    amount = min(amount + val, maxVal);
    emitChangeAmount();
    return amount;
  }
  float MenuItem::decrease(const float val)
  {
    amount = max(amount - val, minVal);
    emitChangeAmount();
    return amount;
  }

  void MenuItem::selectNextItem()
  {
    selectedItem = min(selectedItem++, items.size()-1);
    for (int i = 0; i < items.size(); i++)
    {
      items[i]->setSelected(i == selectedItem);
      editing = false;
    }
  }

  void MenuItem::selectPreviewItem()
  {
    selectedItem = max(selectedItem--, 0);
    for (int i = 0; i < items.size(); i++)
    {
      items[i]->setSelected(i == selectedItem);
      editing = false;
    }
  }

  MenuRenderItem MenuItem::getRender()
  {
    MenuRenderItem result
    {
      this->type,
      this->title,
      this->minVal,
      this->maxVal,
      this->amount,
      this->amountStep,
      this->getAmountLabel(),
      this->selected,
      this->parent != NULL && this->parent->getEditing()
    };

    return result;
  }

  void MenuItem::getRenderItems(Vector<MenuRenderItem> &result)
  {
    for (int i = 0; i < items.size(); i++)   
      result.push_back(items[i]->getRender());
  }
}