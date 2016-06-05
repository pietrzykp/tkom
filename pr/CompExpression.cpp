//
// Created by paulina on 04.06.16.
//

#include "CompExpression.h"

using namespace pr;
using std::string;

CompExpression::CompExpression(std::unique_ptr<Value> leftOperand_,
                                   Operator op_,
                                   std::unique_ptr<Value> rightOperand_)
        : leftOperand(std::move(leftOperand_)),
          rightOperand(std::move(rightOperand_)),
          op(op_)
{}

bool CompExpression::evaluate() const {
    string left = leftOperand->getValue();
    string right = rightOperand->getValue();
    switch(op) {
        case Operator::Equal :
            return left == right;
        case Operator::NotEqual :
            return left != right;
    }

    throw std::runtime_error("Unknown operator");
}

std::string CompExpression::toString() const {
    std::string s = "( ";
    if(leftOperand != nullptr)
        s += leftOperand->toString();
    s += " cmp ";
    if(rightOperand != nullptr)
        s += rightOperand->toString();
    return s + " )";
}