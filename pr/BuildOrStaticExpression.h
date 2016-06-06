//
// Created by paulina on 06.06.16.
//

#ifndef TKOM2_BUILDEXPRESSION_H
#define TKOM2_BUILDEXPRESSION_H


#include "Expression.h"
#include "Value.h"

namespace pr {
    class BuildExpression : public Expression {
        std::unique_ptr<Value> result;
        std::unique_ptr<Value> files;
        std::unique_ptr<Value> flags;
    public:
        BuildExpression(std::unique_ptr<Value> result_, std::unique_ptr<Value> files_, std::unique_ptr<Value> flags_)
                : result(std::move(result_)), files(std::move(files_)), flags(std::move(flags_)) {};
        ~BuildExpression() {};

        bool evaluate() const override {};
        std::string toString() const override;
    };
};
#endif //TKOM2_BUILDEXPRESSION_H
