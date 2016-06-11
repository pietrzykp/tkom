//
// Created by paulina on 05.06.16.
//

#ifndef TKOM2_IFEXPRESSION_H
#define TKOM2_IFEXPRESSION_H

#include <bits/shared_ptr.h>
#include "Expression.h"
#include "OrExpression.h"
#include "Expressions.h"

namespace pr {
    class IfExpression : public Expression {
        std::shared_ptr<Expression> ifClause;
        std::shared_ptr<Expressions> ifExpressions;
        std::shared_ptr<IfExpression> elseIf;
    public:
        IfExpression(std::shared_ptr<Expression> if_, std::shared_ptr<Expressions> expr_, std::shared_ptr<IfExpression> else_)
                : ifClause(std::move(if_)), ifExpressions(std::move(expr_)), elseIf(std::move(else_)) {};

        ~IfExpression() {};

        bool evaluate() const override {};
        std::string toString() const override;
    };
};


#endif //TKOM2_IFEXPRESSION_H
