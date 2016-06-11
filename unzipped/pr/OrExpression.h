//
// Created by paulina on 04.06.16.
//

#ifndef TKOM2_OREXPRESSION_H
#define TKOM2_OREXPRESSION_H


#include <memory>
#include "AndExpression.h"
#include "Expression.h"
#include <vector>
namespace pr {
    class OrExpression : public Expression {
        std::shared_ptr<Expression> leftOperand;
        std::shared_ptr<Expression> rightOperand;
    public:
        OrExpression(std::shared_ptr<Expression> leftOperand_, std::shared_ptr<Expression> rightOperand_);
        ~OrExpression() {};

        bool evaluate() const override;
        std::string toString() const override;
    };
};

#endif //TKOM2_OREXPRESSION_H
