//
// Created by paulina on 06.06.16.
//

#include "BuildOrStaticExpression.h"

std::string pr::BuildExpression::toString() const {
    std::string s;
    s += " build (" + result->toString() + ", " + files->toString() + ", "
         + (flags == nullptr ? " null " : flags ->toString()) + ") endbuild";
    return s;
}

