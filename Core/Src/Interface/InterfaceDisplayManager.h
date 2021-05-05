#ifndef INTERFACE_DISPLAY_MANAGER_H_
#define INTERFACE_DISPLAY_MANAGER_H_

#include <iomanip>
#include <iostream>
#include <sstream>

#include "Interface.h"
#ifdef STM32
#include "SSD1306.h"
#endif

class InterfaceDisplayManager {
   public:
#ifdef STM32
    static void displayManuItem(MenuItem *item, SSD1306* oled);
   private:
    static void displayMenuItemList(MenuItemsList* item, SSD1306* oled);
    static void displayParameter(Parameter* item, SSD1306* oled);
    static void displayAction(Action* item, SSD1306* oled);
    static void displaySwitch(Switch* item, SSD1306* oled);
    static void displayValue(Value* item, SSD1306* oled);
    static void showItem(std::string itemText, uint8_t coordY, uint8_t coordX, SSD1306* oled);
#else
    static void displayManuItem(MenuItem *item);
   private:
    static void displayMenuItemList(MenuItemsList* item);
    static void displayParameter(Parameter* item);
    static void displayAction(Action* item);
    static void displaySwitch(Switch* item);
    static void displayValue(Value* item);
    static void showItem(std::string itemText);
#endif
};
#endif
