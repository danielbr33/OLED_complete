#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <vector>

#include "ArduinoJson-v6.17.3.h"
#include "InterfaceBuilder.h"
#include "InterfaceInput.h"
#include "MenuItem.h"
#include "MenuItemsList.h"
#include "InterfaceJsonKeys.h"

#define DEFAULT_INTERFACE_FILE "Interface.json"

class Interface {
   public:
    Interface();
    Interface(std::string interfaceFilepath);
    void setInputEvent(InterfaceInput::Button event);

    MenuItem *getCurrentMenuItem();

    Action *getActionByName(std::string name);
    void setInterfaceFilepath(std::string filepath);
    std::string getInterfaceFilepath();

    void save();

   private:
    std::string interfaceFilepath = DEFAULT_INTERFACE_FILE;
    MenuItem *mainMenuItem = nullptr;

    MenuItem *getMenuItemByName(std::string name);

    void loadInterface();
};

#endif /* INTERFACE_H_ */
