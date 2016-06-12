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
        std::shared_ptr<Value> leftOperand;
        Operator op;
        std::shared_ptr<Value> rightOperand;
    public:
        CompExpression(std::shared_ptr<Value> leftOperand_, Operator op_, std::shared_ptr<Value> rightOperand_);
        ~CompExpression() {};

        bool evaluate()  override;
        std::string toString() const override;
    };
};


#endif //TKOM2_COMPEXPRESSION_H
