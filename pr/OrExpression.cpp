//
// Created by paulina on 04.06.16.
//

#include "OrExpression.h"
using namespace pr;


OrExpression::OrExpression(std::unique_ptr<Expression> leftOperand_, std::unique_ptr<Expression> rightOperand_) :
        leftOperand(std::move(leftOperand_)), rightOperand(std::move(rightOperand_)) { }

bool OrExpression::evaluate()  {
    if(leftOperand == nullptr)
        return rightOperand->evaluate();
    if(rightOperand == nullptr)
        return leftOperand->evaluate();
    const auto leftValue = leftOperand->evaluate();
    const auto rightValue = rightOperand->evaluate();
    return leftValue || rightValue;
}

std::string OrExpression::toString() const {
    std::string s = "( ";
    if(leftOperand != nullptr)
        s += leftOperand->toString();
    s += " || ";
    if(rightOperand != nullptr)
        s += rightOperand->toString();
    return s + " )";
}

