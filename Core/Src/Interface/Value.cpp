#include "Value.h"

Value::Value(std::string name) : MenuItem(name) {
    type = MenuItem::VALUE;
}

Value::Value(JsonObject jsonObject) : MenuItem(jsonObject) {
    type = MenuItem::VALUE;
    parseValueFromJsonObject(jsonObject);
}

void Value::setInputEvent(InterfaceInput::Button event) {
    switch (event) {
        case InterfaceInput::LEFT_BUTTON:
            break;
        case InterfaceInput::RIGHT_BUTTON:
            break;
        case InterfaceInput::ENTER_BUTTON:
            if (parentMenuItem != nullptr) {
                parentMenuItem->setAsActiveItem();
            }
            break;
        case InterfaceInput::OTHER_BUTTON:
            break;
    }
}

void Value::setValue(VALUE_TYPE value) {
    this->value = value;
}

VALUE_TYPE Value::getValue() {
    return value;
}

void Value::setUnit(std::string unit) {
    this->unit = unit;
}

std::string Value::getUnit() {
    return unit;
}

void Value::setAmountOfDigits(uint8_t digits) {
    amountOfDigits = digits;
}

uint8_t Value::getAmountOfDigits() {
    return amountOfDigits;
}

void Value::prepareValueJsonObject(JsonObject jsonObject) {
    prepareMenuItemJsonObject(jsonObject);
    jsonObject[VALUE_KEY] = value;
    jsonObject[VALUE_DIGITS_KEY] = amountOfDigits;
    jsonObject[VALUE_UNIT_KEY] = unit;
}

void Value::prepareJsonObject(JsonObject jsonObject) {
    prepareValueJsonObject(jsonObject);
}

void Value::parseValueFromJsonObject(JsonObject jsonObject) {
    if ((jsonObject.containsKey(VALUE_KEY)) && (jsonObject[VALUE_KEY].is<VALUE_TYPE>())) {
        setValue(jsonObject[VALUE_KEY].as<VALUE_TYPE>());
    }

    if ((jsonObject.containsKey(VALUE_UNIT_KEY)) && (jsonObject[VALUE_UNIT_KEY].is<std::string>())) {
        setUnit(jsonObject[VALUE_UNIT_KEY].as<std::string>());
    }

    if ((jsonObject.containsKey(VALUE_DIGITS_KEY)) && (jsonObject[VALUE_DIGITS_KEY].is<uint8_t>())) {
        setAmountOfDigits(jsonObject[VALUE_DIGITS_KEY].as<uint8_t>());
    }
}