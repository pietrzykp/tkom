//
// Created by paulina on 05.06.16.
//

#include "IfExpression.h"
#include "VariableStack.h"

std::string pr::IfExpression::toString() const {
    std::string s;
    s += "if " + (ifClause == nullptr ? "null" : ifClause->toString());
    s += " -> " + ifExpressions->toString();
    s += " else " + (elseIf == nullptr ? "null" : elseIf->toString()) + "\n";
    return s;
}

bool pr::IfExpression::evaluate() {
    VariableStack::raiseLevel();
    bool result = ifClause->evaluate();
    if(result)
        ifExpressions->evaluate();
    else if(elseIf != nullptr)
        elseIf->evaluate();
    VariableStack::lowerLevel();
    return true;
}



