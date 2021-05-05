#ifndef INTERFACE_BUILDER_H_
#define INTERFACE_BUILDER_H_

#include <fstream>
#include "MenuItemsList.h"
#include "Parameter.h"
#include "Value.h"
#include "Action.h"
#include "Switch.h"
#include "ArduinoJson-v6.17.3.h"
#include "InterfaceJsonKeys.h"
#include "cardSD.h"

#define JSON_DOCUMENT_SIZE 6000

class InterfaceBuilder {
public:
    static MenuItem* loadInterFaceFromJsonFile(std::string  filepath);
    static MenuItem* loadDefaultInterFace();
    static void loadMenuItemsListFromJsonArray(MenuItemsList* parent, JsonArray array);
    static MenuItem* loadMenuItem(JsonVariant v);
    static void saveInterfaceToFile(MenuItem *item, std::string filepath);
};

#endif 
