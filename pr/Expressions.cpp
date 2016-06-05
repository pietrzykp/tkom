//
// Created by paulina on 05.06.16.
//

#include "Expressions.h"
#include "Expression.h"

std::string pr::Expressions::toString() const {
    std::string s;
    for(int i = 0; i < expressions.size(); ++i)
        s += "expr: " + expressions[i]->toString() + "\n";
    return s;
}

