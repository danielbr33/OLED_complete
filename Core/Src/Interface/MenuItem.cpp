#include "MenuItem.h"

MenuItem::MenuItem(std::string name) {
    this->name = name;
}

MenuItem::MenuItem(JsonObject jsonObject) {
    parseMenuItemFromJsonObject(jsonObject);
}

std::string MenuItem::getName() {
    return name;
}

void MenuItem::setInputEvent(InterfaceInput::Button event) {
    switch (event) {
        case InterfaceInput::LEFT_BUTTON:
            break;
        case InterfaceInput::RIGHT_BUTTON:
            break;
        case InterfaceInput::ENTER_BUTTON:
            break;
        case InterfaceInput::OTHER_BUTTON:
            break;
    }
}

MenuItem* MenuItem::getCurrentMenuItem() {
    return this;
}

MenuItem* MenuItem::getMenuItemByName(std::string name, Type type) {
    if ((name == this->name) && ((type == UNDEFINED) || (type == this->type))) {
        return this;
    }
    return nullptr;
}

void MenuItem::setType(MenuItem::Type type) {
    this->type = type;
}

MenuItem::Type MenuItem::getType() {
    return type;
}

void MenuItem::setAsActiveItem() {
    if (parentMenuItem != nullptr) {
        parentMenuItem->status = ACTIVE_IS_SUBLIST_ITEM;
    }
    status = THIS_IS_ACTIVE_ITEM;
}

std::string MenuItem::getTypeString() {
    switch (type) {
        case PARAMTER:
            return MENU_ITEM_TYPE_PARAMETER;
        case VALUE:
            return MENU_ITEM_TYPE_VALUE;
        case SWITCH:
            return MENU_ITEM_TYPE_SWITCH;
        case ACTION:
            return MENU_ITEM_TYPE_ACTION;
        case MENU_ITEMS_LIST:
            return MENU_ITEM_TYPE_MENU_ITEMS_LIST;
        case UNDEFINED:
            return "";
        case BACK_EVENT_ITEM:
            return "BACK";
    }
    return "";
}

void MenuItem::prepareMenuItemJsonObject(JsonObject jsonObject) {
    jsonObject[MENU_ITEM_NAME_KEY] = name;
    jsonObject[MENU_ITEM_TYPE_KEY] = getTypeString();
}

void MenuItem::prepareJsonObject(JsonObject jsonObject) {
    prepareMenuItemJsonObject(jsonObject);
}

void MenuItem::parseMenuItemFromJsonObject(JsonObject jsonObject) {
    if ((jsonObject.containsKey(MENU_ITEM_NAME_KEY)) && (jsonObject[MENU_ITEM_NAME_KEY].is<std::string>())) {
        name = (jsonObject[MENU_ITEM_NAME_KEY].as<std::string>());
    }
}
