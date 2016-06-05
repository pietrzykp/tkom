//
// Created by paulina on 05.06.16.
//

#include "IfExpression.h"

std::string pr::IfExpression::toString() const {
    std::string s;
    s += "if " + (ifClause == nullptr ? "null" : ifClause->toString());
    s += " -> " + ifExpressions->toString();
    s += " else " + (elseIf == nullptr ? "null" : elseIf->toString()) + "\n";
    return s;
}

