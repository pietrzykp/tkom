//
// Created by paulina on 05.06.16.
//

#ifndef TKOM2_FUNDEF_H
#define TKOM2_FUNDEF_H


#include "Expression.h"
#include "Expressions.h"
#include "Value.h"

namespace pr {
    class FunctionDeclaration: public Expression {
        std::string label;
        std::vector<std::string> params;
        std::unique_ptr<Expressions> expressions;
    public:
        FunctionDeclaration(std::string label_, std::vector<std::string> params_, std::unique_ptr<Expressions> expr_)
                : label(label_), params(std::move(params_)), expressions(std::move(expr_)) {};
        ~FunctionDeclaration() {};
        std::string getLabel() {return label;};
        bool evaluate()  override;
        bool execute(std::vector<std::shared_ptr<Value> > & values);
        std::string toString() const override;
    };
};


#endif //TKOM2_FUNDEF_H
