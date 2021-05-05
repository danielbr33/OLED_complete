#ifndef MENU_ITEMS_LIST_H_
#define MENU_ITEMS_LIST_H_

#include <vector>

#include "MenuItem.h"

#define DEFAULT_MENU_ITEMS_LIST_NAME "MenuItemsList"

class MenuItemsList : public MenuItem {

   public:
    MenuItemsList(std::string name = DEFAULT_MENU_ITEMS_LIST_NAME);
    MenuItemsList(JsonObject jsonObject);

    void addItemToList(MenuItem* menuItem);
    void setInputEvent(InterfaceInput::Button event);

    MenuItem* getCurrentMenuItem();
    MenuItem* getSelectedMenuItem();

    MenuItem* getMenuItemByName(std::string name, Type type = UNDEFINED);

    void prepareJsonObject(JsonObject jsonObject);

   private:
    std::vector<MenuItem*> subMenuItems;

    void moveLeft();
    void moveRight();

    

    uint16_t currentMainMenuItem = 0;
};

#endif
