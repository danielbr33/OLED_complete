#include "InterfaceBuilder.h"

MenuItem* InterfaceBuilder::loadInterFaceFromJsonFile(std::string filepath) {
    StaticJsonDocument<JSON_DOCUMENT_SIZE> doc;
#ifdef STM32
    char* data;
	cardSD::SD_Status sd_status;
    sd_status = cardSD::getInstance().readFile((char*)filepath.c_str(), &data);
    DeserializationError error = deserializeJson(doc, data);
    if (error == 0)
        return loadMenuItem(doc.as<JsonVariant>());
#else
    std::ifstream interfaceJsonFile(filepath);
    DeserializationError error = deserializeJson(doc, interfaceJsonFile);
    if (error) {
        std::cout << filepath;
        std::cout << " Json deserialize failed: ";
        std::cout << error << std::endl;
    } else {
        return loadMenuItem(doc.as<JsonVariant>());
    }
#endif
    return nullptr;
}

void InterfaceBuilder::loadMenuItemsListFromJsonArray(MenuItemsList* parent, JsonArray array) {
    for (JsonVariant v : array) {
        MenuItem* item = loadMenuItem(v);
        if (item != nullptr) {
            parent->addItemToList(item);
        }
    }
}

MenuItem* InterfaceBuilder::loadMenuItem(JsonVariant v) {
    if (v.containsKey(MENU_ITEM_TYPE_KEY)) {
        if (v[MENU_ITEM_TYPE_KEY].as<std::string>() == MENU_ITEM_TYPE_VALUE) {
            return new Value(v.as<JsonObject>());
        } else if (v[MENU_ITEM_TYPE_KEY].as<std::string>() == MENU_ITEM_TYPE_PARAMETER) {
            return new Parameter(v.as<JsonObject>());
        } else if (v[MENU_ITEM_TYPE_KEY].as<std::string>() == MENU_ITEM_TYPE_SWITCH) {
            return new Switch(v.as<JsonObject>());
        } else if (v[MENU_ITEM_TYPE_KEY].as<std::string>() == MENU_ITEM_TYPE_ACTION) {
            return new Action(v.as<JsonObject>());
        } else if (v[MENU_ITEM_TYPE_KEY].as<std::string>() == MENU_ITEM_TYPE_MENU_ITEMS_LIST) {
            MenuItemsList* menuItemsList = new MenuItemsList(v.as<JsonObject>());
            loadMenuItemsListFromJsonArray(menuItemsList, v[MENU_ITEMS_LIST_KEY].as<JsonArray>());
            return menuItemsList;
        }
    }
    return nullptr;
}

MenuItem* InterfaceBuilder::loadDefaultInterFace() {
    MenuItemsList* mainMenu = new MenuItemsList("Main Menu");

    mainMenu->addItemToList(new Parameter("U battery"));
    mainMenu->addItemToList(new Parameter("Work time"));
    mainMenu->addItemToList(new Parameter("Distance"));
    mainMenu->addItemToList(new Parameter("En consumed"));
    mainMenu->addItemToList(new Parameter("Temperature"));

    MenuItemsList* pid = new MenuItemsList("pid");
    pid->addItemToList(new Parameter("P"));
    pid->addItemToList(new Parameter("I"));
    pid->addItemToList(new Parameter("D"));

    mainMenu->addItemToList(pid);

    return mainMenu;
}

void InterfaceBuilder::saveInterfaceToFile(MenuItem* item, std::string filepath) {
    StaticJsonDocument<JSON_DOCUMENT_SIZE> jsonDocument;
    JsonObject jsonObject = jsonDocument.to<JsonObject>();
    item->prepareJsonObject(jsonObject);

    std::ofstream outputFileStream(filepath, std::ofstream::out);
    // serializeJson(jsonDocument, ofs);
    serializeJsonPretty(jsonDocument, outputFileStream);
    outputFileStream.close();
}
