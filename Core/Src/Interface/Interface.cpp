#include "Interface.h"

Interface::Interface() {
    loadInterface();
}

Interface::Interface(std::string interfaceFilepath) {
    this->interfaceFilepath = interfaceFilepath;
    loadInterface();
}

void Interface::loadInterface() {
    mainMenuItem = InterfaceBuilder::loadInterFaceFromJsonFile(interfaceFilepath);
    if (mainMenuItem == nullptr) {
        mainMenuItem = InterfaceBuilder::loadDefaultInterFace();
    }
}

void Interface::setInterfaceFilepath(std::string filepath) {
    this->interfaceFilepath = filepath;
}
std::string Interface::getInterfaceFilepath() {
    return interfaceFilepath;
}

void Interface::setInputEvent(InterfaceInput::Button event) {
    mainMenuItem->getCurrentMenuItem()->setInputEvent(event);
}

MenuItem* Interface::getCurrentMenuItem() {
    return mainMenuItem->getCurrentMenuItem();
}

MenuItem* Interface::getMenuItemByName(std::string name) {
    return mainMenuItem->getMenuItemByName(name);
}

Action* Interface::getActionByName(std::string name) {
    return (Action*)mainMenuItem->getMenuItemByName(name, MenuItem::ACTION);
}

void Interface::save() {
    InterfaceBuilder::saveInterfaceToFile(mainMenuItem, interfaceFilepath);
}
