//
// Created by paulina on 05.06.16.
//

#include "VariableDeclaration.h"
using namespace pr;

std::string VariableDeclaration::toString() const {
    return "decl " + label + ": " + value->toString();
}

