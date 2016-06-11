//
// Created by paulina on 06.06.16.
//

#include "BuildOrStaticExpression.h"

std::string pr::BuildOrStaticExpression::toString() const {
    std::string s;
    std::string b = (function == EndFunction::Build ? "build" : "staticlib");
    s += b + " (" + result->toString() + ", " + files->toString() + ", "
         + (flags == nullptr ? " null " : flags ->toString()) + ") endbuild";
    return s;
}

