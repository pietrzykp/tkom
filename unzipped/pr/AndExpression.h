//
// Created by paulina on 04.06.16.
//

#ifndef TKOM2_ANDEXPRESSION_H
#define TKOM2_ANDEXPRESSION_H

#include <memory>
#include "CompExpression.h"
#include "Expression.h"

namespace pr {
    class AndExpression : public Expression {
        std::unique_ptr<Expression> leftOperand;
        std::unique_ptr<Expression> rightOperand;
    public:
        AndExpression(std::unique_ptr<Expression> leftOperand_, std::unique_ptr<Expression> rightOperand_);
        ~AndExpression() {};

        bool evaluate() const override;
        std::string toString() const override;
    };
};


#endif //TKOM2_ANDEXPRESSION_H