//
// Created by paulina on 05.06.16.
//

#ifndef TKOM2_FUNDEF_H
#define TKOM2_FUNDEF_H


#include "Expression.h"
#include "Expressions.h"

namespace pr {
    class FunctionDeclaration: public Expression {
        std::string label;
        std::vector<std::string> params;
        std::shared_ptr<Expressions> expressions;
    public:
        FunctionDeclaration(std::string label_, std::vector<std::string> params_, std::shared_ptr<Expressions> expr_)
                : label(label_), params(std::move(params_)), expressions(std::move(expr_)) {};
        ~FunctionDeclaration() {};

        bool evaluate() const override {};
        std::string toString() const override;
    };
};


#endif //TKOM2_FUNDEF_H
