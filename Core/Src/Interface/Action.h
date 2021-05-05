#ifndef ACTION_H_
#define ACTION_H_

#include <mainInterface.h>
#include "Switch.h"

#define DEFAULT_ACTION_NAME "Action"

class Action : public Switch {
   public:
    Action(std::string name = DEFAULT_ACTION_NAME);
    Action(JsonObject jsonObject);
    void setInputEvent(InterfaceInput::Button event);
    void setFunction(void (*function)());


   private:
    void (*function)() = nullptr;
};

#endif
