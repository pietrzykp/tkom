//
// Created by paulina on 04.06.16.
//

#include "Value.h"
using namespace pr;

std::unordered_map<std::string, std::unique_ptr<Value> > variables = {};

std::string Value::getValue() {
    if(!singleValue)
        return arrayValue[0]->getValue();
    if(!searchValue)
        return value;
    else
        return variables[value]->getValue();
}

std::string Value::toString() {
    if(singleValue) {
        if(!searchValue)
            return value;
        else
            return variables[value]->toString();
    }
    std::string s = " [- ";
    for(int i = 0; i < arrayValue.size(); ++i)
        s += arrayValue[i]->toString() + ", ";
    s += " -] \n";
    return s;
}

