//
// Created by paulina on 05.06.16.
//

#ifndef TKOM2_EXPRESSIONS_H
#define TKOM2_EXPRESSIONS_H


#include <memory>
#include <vector>
#include "Expression.h"

namespace pr {
    class Expressions : public Expression {
        std::vector<std::unique_ptr<Expression> > expressions;
    public:
        Expressions(std::vector<std::unique_ptr<Expression> > vec) : expressions(std::move(vec)) {};
        ~Expressions() {};

        bool evaluate() const override {};
        std::string toString() const override;
    };
};

#endif //TKOM2_EXPRESSIONS_H
