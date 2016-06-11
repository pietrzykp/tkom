//
// Created by paulina on 05.06.16.
//

#include "VariableDeclaration.h"
#include "Value.h"
#include "VariableStack.h"

using namespace pr;

std::string VariableDeclaration::toString() const {
    return "decl " + label + ": " + value->toString();
}

bool VariableDeclaration::evaluate()  {
    VariableStack::putValue(value, label);
    return true;
}



