//
// Created by paulina on 05.06.16.
//

#include "FunctionDeclaration.h"
#include "FunctionStack.h"
#include "VariableStack.h"

using namespace pr;

std::string FunctionDeclaration::toString() const {
    std::string s;
    s += "fundef " + label;
    s += " params: ";
    for(int i = 0; i < params.size(); ++i)
        s += params[i] + " ";
    s += " funins " + expressions->toString();
    s += " endfundef \n";
    return s;
}

bool FunctionDeclaration::evaluate() {
    FunctionStack::decl.push_back(std::shared_ptr<FunctionDeclaration>(this));
}

bool FunctionDeclaration::execute(std::vector<std::shared_ptr<Value> > &values) {
    if(values.size() != params.size())
        return false;
    VariableStack::raiseLevel();
    for(int i = 0; i < values.size(); ++i) {
        VariableStack::putValue(values[i], params[i]);
    }
    expressions->evaluate();
    VariableStack::lowerLevel();
    return true;
}



