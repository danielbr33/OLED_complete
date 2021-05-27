#include "InterfaceManager.h"

Interface* InterfaceManager::interfaceLocal = nullptr;

#define BUTTON_NOT_PRESSED 		255
#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
    #include <conio.h>
#endif

#ifdef __linux__
    #include <ncurses.h>
    #include <unistd.h>

void prepareNcurses();
int kbhit(void);

    #include <chrono>
    #include <cstdio>

    #define BUTTON_1       68  // left
    #define BUTTON_2       67  // right
    #define BUTTON_3       66  // down
    #define SPECIAL_BUTTON 91

#elif defined(_WIN32) || defined(_WIN64)
    #define BUTTON_1       75  // left
    #define BUTTON_2       77  // right
    #define BUTTON_3       80  // down
    #define SPECIAL_BUTTON 224

#elif defined(STM32)
    #define BUTTON_1       97  // left
    #define BUTTON_2       100  // right
    #define BUTTON_3       119  // down
    #define SPECIAL_BUTTON 224

#endif

#define INTERVAL 0.1

void InterfaceManager::saveInterface() {
    interfaceLocal->save();
}

#ifdef STM32
InterfaceManager::InterfaceManager(UART_HandleTypeDef* uart, SSD1306* oled){
#elif
InterfaceManager::InterfaceManager() {
#endif

#ifdef __linux__
    prepareNcurses();
#endif
#ifdef STM32
    this->oled = oled;
    this->interfaceUart = uart;
#endif
    interfaceLocal = new Interface("Interface.json");

    Action* saveAction = interfaceLocal->getActionByName("Save");
    if (saveAction != nullptr) {
        saveAction->setFunction(&(this->saveInterface));
    }

    //display();
	this->button = BUTTON_NOT_PRESSED;
    while (true) {
#ifdef __linux__
        if (kbhit()) {
            if (getch() == SPECIAL_BUTTON) {
                interfaceLocal->setInputEvent(readKey());
            }
        } else {
            usleep(100000);
            display();
        }
#elif defined(_WIN32) || defined(_WIN64)
        if (_kbhit()) {
            if (_getch() == SPECIAL_BUTTON) {
                interfaceLocal->setInputEvent(readKey());
            }
        } else {
            usleep(100000);
            display();
        }
#elif defined(STM32)
        if(button != BUTTON_NOT_PRESSED){
        	interfaceLocal->setInputEvent(readKey());
        	button = BUTTON_NOT_PRESSED;
        }
        else {
        	display();
        	osDelay(10);
        }
        HAL_UART_Receive_IT(interfaceUart, (uint8_t*)&button, 1);
    }
}
#endif

InterfaceInput::Button InterfaceManager::readKey() {
#ifdef __linux__
    switch (getch()) {
#elif defined(_WIN32) || defined(_WIN64)
    switch (_getch()) {
#elif defined(STM32)
    switch (button) {
#endif
        case BUTTON_1:
            return InterfaceInput::LEFT_BUTTON;
        case BUTTON_2:
            return InterfaceInput::RIGHT_BUTTON;
        case BUTTON_3:
            return InterfaceInput::ENTER_BUTTON;
            break;
    }
    return InterfaceInput::OTHER_BUTTON;
}
void InterfaceManager::display() {
#ifdef __linux__
    clear();
#elif defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif

    MenuItem* currentItem = interfaceLocal->getCurrentMenuItem();
    InterfaceDisplayManager::displayManuItem(currentItem, this->oled);
#ifdef __linux__
    refresh();
#endif
}

#ifdef __linux__
int kbhit(void) {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void prepareNcurses() {
    initscr();

    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    scrollok(stdscr, TRUE);
}

#endif

#if defined(_WIN32) || defined(_WIN64)
void InterfaceManager::usleep(__int64 usec) {
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * usec);  // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}
#endif
