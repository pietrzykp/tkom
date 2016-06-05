//
// Created by paulina on 04.06.16.
//

#include "AndExpression.h"
using namespace pr;


AndExpression::AndExpression(std::unique_ptr<Expression> leftOperand_, std::unique_ptr<Expression> rightOperand_) :
        leftOperand(std::move(leftOperand_)), rightOperand(std::move(rightOperand_)) { }

bool AndExpression::evaluate() const {
    if(rightOperand == nullptr)
        return leftOperand->evaluate();
    if(leftOperand == nullptr)
        return rightOperand->evaluate();
    const auto leftValue = leftOperand->evaluate();
    const auto rightValue = rightOperand->evaluate();
    return leftValue && rightValue;
}

std::string AndExpression::toString() const {
    std::string s = "( ";
    if(leftOperand != nullptr)
        s += leftOperand->toString();
    s += " && ";
    if(rightOperand != nullptr)
        s += rightOperand->toString();
    return s + " )";
}