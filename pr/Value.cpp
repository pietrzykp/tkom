//
// Created by paulina on 04.06.16.
//

#include "Value.h"
#include "VariableStack.h"

using namespace pr;

std::string Value::toString() {
    if(singleValue) {
        if(!searchValue)
            return value;
        else
            return VariableStack::getValue(value)->toString();
    }
    std::string s = " [- ";
    for(int i = 0; i < arrayValue.size(); ++i)
        s += arrayValue[i]->toString() + ", ";
    s += " -] \n";
    return s;
}

std::shared_ptr<Value> Value::getByIndex(int index) {
    if(singleValue)
        return std::shared_ptr<Value>(this);
    return arrayValue[index];
}

void Value::getAllValues(std::vector<std::string>& vec) {
    if(singleValue)
        vec.push_back(value);
    else {
        for(int i = 0; i < arrayValue.size(); ++i) {
            arrayValue[i]->getAllValues(vec);
        }
    }
}

std::string Value::getSingleValue() {
    if(!singleValue)
        return arrayValue[0]->getSingleValue();
    if(!searchValue)
        return value;
    else
        return VariableStack::getValue(value)->getSingleValue();
}

std::shared_ptr<Value> Value::getNonSearchValue() {
    if(!searchValue)
        return shared_from_this();
    return
        VariableStack::getValue(value)->getNonSearchValue();
}









