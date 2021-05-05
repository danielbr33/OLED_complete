#include "MenuItemsList.h"

MenuItemsList::MenuItemsList(std::string name) : MenuItem(name) {
    this->type = MENU_ITEMS_LIST;

    MenuItem* backItem = new MenuItem("Back");
    backItem->setType(BACK_EVENT_ITEM);
    backItem->parentMenuItem = this;
    backItem->parentMenuItem = this;
    subMenuItems.push_back(backItem);
}

MenuItemsList::MenuItemsList(JsonObject jsonObject) : MenuItem(jsonObject) {
    this->type = MENU_ITEMS_LIST;

    MenuItem* backItem = new MenuItem("Back");
    backItem->setType(BACK_EVENT_ITEM);
    backItem->parentMenuItem = this;
    backItem->parentMenuItem = this;
    subMenuItems.push_back(backItem);
}

void MenuItemsList::addItemToList(MenuItem* menuItem) {
    menuItem->parentMenuItem = this;
    subMenuItems.push_back(menuItem);
    if (currentMainMenuItem == 0) {
        currentMainMenuItem = 1;
    }
}

void MenuItemsList::setInputEvent(InterfaceInput::Button event) {
    switch (event) {
        case InterfaceInput::LEFT_BUTTON:
            moveLeft();
            break;
        case InterfaceInput::RIGHT_BUTTON:
            moveRight();
            break;
        case InterfaceInput::ENTER_BUTTON:
            if ((getSelectedMenuItem()->type == BACK_EVENT_ITEM) && (parentMenuItem != nullptr)) {
                parentMenuItem->setAsActiveItem();
            } else if (getSelectedMenuItem()->type != UNDEFINED) {
                getSelectedMenuItem()->setAsActiveItem();
            }
            break;
        case InterfaceInput::OTHER_BUTTON:
            break;
    }
}

void MenuItemsList::moveLeft() {
    uint16_t minimalElementIndex = 0;
    if (parentMenuItem == nullptr) {
        minimalElementIndex = 1;  //Dont show back element when item dont has parent
    }

    if (subMenuItems.size() > 0) {
        if (currentMainMenuItem > minimalElementIndex) {
            currentMainMenuItem--;
        } else {
            currentMainMenuItem = subMenuItems.size() - 1;
        }
    }
}

void MenuItemsList::moveRight() {
    uint16_t minimalElementIndex = 0;
    if (parentMenuItem == nullptr) {
        minimalElementIndex = 1;  //Dont show back element when item dont has parent
    }

    if (subMenuItems.size() > 0) {
        if (currentMainMenuItem < (subMenuItems.size() - 1)) {
            currentMainMenuItem++;
        } else {
            currentMainMenuItem = minimalElementIndex;
        }
    }
}

MenuItem* MenuItemsList::getCurrentMenuItem() {
    if (status == ACTIVE_IS_SUBLIST_ITEM) {
        return subMenuItems[currentMainMenuItem]->getCurrentMenuItem();
    }
    return this;
}

MenuItem* MenuItemsList::getSelectedMenuItem() {
    return subMenuItems[currentMainMenuItem];
}

MenuItem* MenuItemsList::getMenuItemByName(std::string name, Type type) {
    if ((name == this->name) && ((type == UNDEFINED) || (type == this->type))) {
        return this;
    } else {
        for (MenuItem* item : subMenuItems) {
            MenuItem* foundItem = item->getMenuItemByName(name);
            if (foundItem != nullptr) {
                return foundItem;
            }
        }
    }
    return nullptr;
}

void MenuItemsList::prepareJsonObject(JsonObject jsonObject) {
    jsonObject[MENU_ITEM_NAME_KEY] = name;
    jsonObject[MENU_ITEM_TYPE_KEY] = getTypeString();
    JsonArray jsonArray = jsonObject.createNestedArray(MENU_ITEMS_LIST_KEY);
    for (MenuItem* item : subMenuItems) {
        if (item->getType() != BACK_EVENT_ITEM) {
            item->prepareJsonObject(jsonArray.createNestedObject());
        }
    }
}
