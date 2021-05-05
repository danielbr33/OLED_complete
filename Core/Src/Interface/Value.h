#ifndef VALUE_H_
#define VALUE_H_
#include "InterfaceInput.h"
#include "MenuItem.h"

#define DEFAULT_VALUE_NAME "Value"

#define VALUE_TYPE  float
#define INT16_T_MIN -32768
#define INT16_T_MAX 32767

class Value : public MenuItem {
   public:
    Value(std::string name = DEFAULT_VALUE_NAME);
    Value(JsonObject jsonObject);
    void setInputEvent(InterfaceInput::Button event);

    void setValue(VALUE_TYPE value);
    VALUE_TYPE getValue();

    void setUnit(std::string unit);
    std::string getUnit();

    void setAmountOfDigits(uint8_t digits);
    uint8_t getAmountOfDigits();

    void prepareJsonObject(JsonObject jsonObject);

   protected:
    VALUE_TYPE value = 0;
    uint8_t amountOfDigits = 0;
    std::string unit = "";

    void prepareValueJsonObject(JsonObject jsonObject);

   private:
    void parseValueFromJsonObject(JsonObject jsonObject);
};

#endif
