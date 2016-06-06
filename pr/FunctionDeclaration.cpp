//
// Created by paulina on 05.06.16.
//

#include "FunctionDeclaration.h"
std::string FunDef::toString() const {
    std::string s;
    s += "fundef " + label;
    s += " params: ";
    for(int i = 0; i < params.size(); ++i)
        s += params[i] + " ";
    s += " funins " + expressions->toString();
    s += " endfundef \n";
    return s;
}