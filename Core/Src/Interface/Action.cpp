#include "Action.h"

Action::Action(std::string name) : Switch(name) {
    type = MenuItem::ACTION;
}

Action::Action(JsonObject jsonObject) : Switch(jsonObject){
    type = MenuItem::ACTION;
}

void Action::setInputEvent(InterfaceInput::Button event) {
    switch (event) {
        case InterfaceInput::LEFT_BUTTON:
            value = false;
            break;
        case InterfaceInput::RIGHT_BUTTON:
            value = true;
            break;
        case InterfaceInput::ENTER_BUTTON:
            if ((value) && (function != nullptr)) {
                value = false;
                function();
            }
            if (parentMenuItem != nullptr) {
                parentMenuItem->setAsActiveItem();
            }
            break;
        case InterfaceInput::OTHER_BUTTON:
            break;
    }
}

void Action::setFunction(void (*function)()) {
    this->function = function;
}