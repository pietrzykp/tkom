//
// Created by paulina on 05.06.16.
//

#ifndef TKOM2_FUNCTIONDECLARATION_H
#define TKOM2_FUNCTIONDECLARATION_H

#include <string>
#include "Expression.h"
#include "Value.h"

namespace pr {
    class FunctionCall : public Expression {
        std::string label;
        std::vector<std::shared_ptr<Value> > values;
    public:
        FunctionCall(std::string label_, std::vector<std::shared_ptr<Value> > values_)
                : label(label_), values(std::move(values_)) {};
        ~FunctionCall() {};

        bool evaluate() const override {};
        std::string toString() const override;
    };
};


#endif //TKOM2_FUNCTIONDECLARATION_H
