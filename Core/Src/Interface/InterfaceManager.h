#ifndef INTERFACE_MANAGER_H_
#define INTERFACE_MANAGER_H_
#include <iostream>

#include "Interface.h"
#include "InterfaceInput.h"
#include "InterfaceDisplayManager.h"
#include "usart.h"

class InterfaceManager {
   public:
#ifdef STM32
	InterfaceManager(UART_HandleTypeDef* huart, SSD1306* oled);
#else
    InterfaceManager();
#endif
    static void saveInterface();

   private:
    static Interface *interfaceLocal;

    InterfaceInput::Button readKey();
    void display();
#if defined(_WIN32) || defined(_WIN64)
    void usleep(__int64 usec);
#endif
#if defined (STM32)
    UART_HandleTypeDef* interfaceUart;
    SSD1306* oled;
#endif
    uint8_t button;
};
#endif /* INTERFACEMANAGER_H_ */
