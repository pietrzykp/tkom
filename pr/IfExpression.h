//
// Created by paulina on 05.06.16.
//

#ifndef TKOM2_IFEXPRESSION_H
#define TKOM2_IFEXPRESSION_H

#include <bits/unique_ptr.h>
#include "Expression.h"
#include "OrExpression.h"
#include "Expressions.h"

namespace pr {
    class IfExpression : public Expression {
        std::unique_ptr<Expression> ifClause;
        std::unique_ptr<Expressions> ifExpressions;
        std::unique_ptr<IfExpression> elseIf;
    public:
        IfExpression(std::unique_ptr<Expression> if_, std::unique_ptr<Expressions> expr_, std::unique_ptr<IfExpression> else_)
                : ifClause(std::move(if_)), ifExpressions(std::move(expr_)), elseIf(std::move(else_)) {};

        ~IfExpression() {};

        bool evaluate() const override {};
        std::string toString() const override;
    };
};


#endif //TKOM2_IFEXPRESSION_H
