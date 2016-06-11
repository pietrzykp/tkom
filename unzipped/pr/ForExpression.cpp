//
// Created by paulina on 06.06.16.
//

#include "ForExpression.h"

std::string pr::ForExpression::toString() const {
    std::string s;
    s += "for (";
    for(int i = 0; i < lists.size(); ++i)
        s += " , " + paramNames[i] + " : " + lists[i]->toString();
    s += " )";
    s += expressions->toString();
    s += " endfor ";
    return s;
}

