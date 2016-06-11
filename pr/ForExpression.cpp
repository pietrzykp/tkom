//
// Created by paulina on 06.06.16.
//

#include "ForExpression.h"
#include "VariableStack.h"

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

bool pr::ForExpression::evaluate() {
    /*if(paramNames.size() != lists.size())
        return false;
    for(int i = 0; i < lists.size(); ++i) {
        lists[i] = lists[i]->getNonSearchValue();
    }
    int size = lists[0]->getSize();
    for(int i = 1; i < lists.size(); ++i)
        if(lists[i]->getSize() != size)
            return false;

    for(int i = 0; i < size; ++i) {
        VariableStack::raiseLevel();
        for(int j = 0; j < paramNames.size(); ++j)
            VariableStack::putValue(lists[j]->getByIndex(i), paramNames[j]);
        expressions->evaluate();
        VariableStack::lowerLevel();
    }*/
    return true;
}


