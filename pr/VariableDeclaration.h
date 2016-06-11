//
// Created by paulina on 05.06.16.
//

#ifndef TKOM2_VARIABLEDECLARATION_H
#define TKOM2_VARIABLEDECLARATION_H

#include <memory>
#include "Expression.h"
#include "Value.h"

namespace pr {
    class VariableDeclaration : public Expression {
        std::string label;
        std::shared_ptr<Value> value;
    public:
        VariableDeclaration(std::string label_, std::shared_ptr<Value> value_)
                : label(label_), value(std::move(value_)) {};
        ~VariableDeclaration() {};

        bool evaluate()  override;
        std::string toString() const override;
    };
};

#endif //TKOM2_VARIABLEDECLARATION_H
