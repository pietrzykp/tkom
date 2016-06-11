//
// Created by paulina on 06.06.16.
//

#ifndef TKOM2_FOREXPRESSION_H
#define TKOM2_FOREXPRESSION_H


#include "Expression.h"
#include "Value.h"
#include "Expressions.h"

namespace pr {
    class ForExpression: public Expression {
        std::vector<std::string> paramNames;
        std::vector<std::shared_ptr<Value> > lists;
        std::unique_ptr<Expressions> expressions;
    public:
        ForExpression(std::vector<std::string> names_, std::vector<std::shared_ptr<Value> > lists_, std::unique_ptr<Expressions> expr_)
                : paramNames(names_), lists(std::move(lists_)), expressions(std::move(expr_)) {};
        ~ForExpression() {};

        bool evaluate() const override {};
        std::string toString() const override;
    };
};

#endif //TKOM2_FOREXPRESSION_H
