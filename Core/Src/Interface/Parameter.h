#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "Value.h"

#define DEFAULT_PARAMETER_NAME "Parameter"

class Parameter : public Value {
   public:
    Parameter(std::string name = DEFAULT_PARAMETER_NAME);
    Parameter(JsonObject jsonObject);
    void setInputEvent(InterfaceInput::Button event);

    void setMinValue(VALUE_TYPE minValue);
    void setMaxValue(VALUE_TYPE maxValue);
    void setValueChange(VALUE_TYPE change);

    void prepareJsonObject(JsonObject jsonObject);

   private:
    VALUE_TYPE minValue = INT16_T_MIN;
    VALUE_TYPE maxValue = INT16_T_MAX;

    VALUE_TYPE valueChange = 1;

    void decrementValue();
    void incrementValue();
    void parseParameterFromJsonObject(JsonObject jsonObject);
};

#endif
