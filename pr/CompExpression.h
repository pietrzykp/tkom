//
// Created by paulina on 04.06.16.
//

#ifndef TKOM2_COMPEXPRESSION_H
#define TKOM2_COMPEXPRESSION_H

#include <string>
#include <memory>
#include "Expression.h"
#include "Operator.h"
#include "Value.h"

namespace pr {
    class CompExpression : public Expression {
        std::unique_ptr<Value> leftOperand;
        Operator op;
        std::unique_ptr<Value> rightOperand;
    public:
        CompExpression(std::unique_ptr<Value> leftOperand_, Operator op_, std::unique_ptr<Value> rightOperand_);
        ~CompExpression() {};

        bool evaluate() const override;
        std::string toString() const override;
    };
};


#endif //TKOM2_COMPEXPRESSION_H
