#include "InterfaceDisplayManager.h"
#include "SSD1306.h"

#ifdef STM32
void InterfaceDisplayManager::displayManuItem(MenuItem* item, SSD1306* oledPointer) {
#else
void InterfaceDisplayManager::displayManuItem(MenuItem* item) {
#endif
    switch (item->getType()) {
        case MenuItem::MENU_ITEMS_LIST:
            displayMenuItemList((MenuItemsList*)item, oledPointer);
            break;
        case MenuItem::PARAMTER:
            displayParameter((Parameter*)item, oledPointer);
            break;
        case MenuItem::VALUE:
            displayValue((Value*)item, oledPointer);
            break;
        case MenuItem::SWITCH:
            displaySwitch((Switch*)item, oledPointer);
            break;
        case MenuItem::ACTION:
            displayAction((Action*)item, oledPointer);
            break;
        case MenuItem::UNDEFINED:
        case MenuItem::BACK_EVENT_ITEM:
            break;
    }
}

#ifdef STM32
void InterfaceDisplayManager::showItem(std::string itemText, uint8_t coordY, uint8_t coordX, SSD1306* oled) {
#ifdef INTERFACE_DEFAULT_MODE
    oled->writeDefaultString((char*)itemText.c_str(), BufferSSD1306::White, 2, 2);
#else
    oled->writeString((char*)itemText.c_str(), 7, 10, BufferSSD1306::White, coordY, coordX);
#endif
}
#else
	void InterfaceDisplayManager::showItem(std::string itemText){
#ifdef __linux__
    printw("%s", itemText.c_str());
#elif defined(_WIN32) || defined(_WIN64)
    std::cout << itemText;
#endif
#endif

#ifdef STM32
void InterfaceDisplayManager::displayMenuItemList(MenuItemsList* item, SSD1306* oled) {
#else
void InterfaceDisplayManager::displayMenuItemList(MenuItemsList* item) {
#endif
    std::ostringstream stringStream;
    stringStream << item->getName() << std::endl;
    stringStream << "  > " << item->getSelectedMenuItem()->getName();
#ifdef STM32
    showItem(stringStream.str(), 2, 2, oled);
#else
    showItem(stringStream.str());
#endif
}

#ifdef STM32
void InterfaceDisplayManager::displayParameter(Parameter* item, SSD1306* oled) {
#else
void InterfaceDisplayManager::displayParameter(Parameter* item) {
#endif
    std::ostringstream stringStream;
    stringStream << item->getName() << std::endl;
    stringStream << "-   " << std::fixed << std::setprecision(item->getAmountOfDigits()) << item->getValue() << " " << item->getUnit() << "   +" << std::endl;
#ifdef STM32
    showItem(stringStream.str(), 2, 30, oled);
#else
    showItem(stringStream.str());
#endif
}

#ifdef STM32
void InterfaceDisplayManager::displayAction(Action* item, SSD1306* oled) {
#else
void InterfaceDisplayManager::displayAction(Action* item) {
#endif
    std::ostringstream stringStream;
    stringStream << item->getName() << std::endl;
    if (item->getValue()) {
        stringStream << " NO    [YES]    | editing" << std::endl;
    } else {
        stringStream << "[NO]    YES     | editing" << std::endl;
    }
#ifdef STM32
    showItem(stringStream.str(), 22, 2, oled);
#else
    showItem(stringStream.str());
#endif
}

#ifdef STM32
void InterfaceDisplayManager::displaySwitch(Switch* item, SSD1306* oled) {
#else
void InterfaceDisplayManager::displaySwitch(Switch* item) {
#endif
	std::ostringstream stringStream;
    stringStream << item->getName() << std::endl;
    if (item->getValue()) {
        stringStream << " OFF    [ON]    | editing" << std::endl;
    } else {
        stringStream << "[OFF]    ON     | editing" << std::endl;
    }
#ifdef STM32
    showItem(stringStream.str(), 22, 30, oled);
#else
    showItem(stringStream.str());
#endif
}

#ifdef STM32
void InterfaceDisplayManager::displayValue(Value* item, SSD1306* oled) {
#else
void InterfaceDisplayManager::displayValue(Value* item) {
#endif
    std::ostringstream stringStream;
    stringStream << item->getName() << std::endl;
    stringStream << "   " << std::fixed << std::setprecision(item->getAmountOfDigits()) << item->getValue() << " " << item->getUnit() << "   " << std::endl;
#ifdef STM32
    showItem(stringStream.str(), 42, 2, oled);
#else
    showItem(stringStream.str());
#endif
}
