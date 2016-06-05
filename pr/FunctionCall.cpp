//
// Created by paulina on 05.06.16.
//

#include "FunctionCall.h"

std::string pr::FunctionCall::toString() const {
    std::string s;
    s += "call " + label;
    s += " params : ";
    for(int i = 0; i < values.size(); ++i) {
        s += values[i]->toString() + ", ";
    }
    s += "endcall\n";
    return s;
}

