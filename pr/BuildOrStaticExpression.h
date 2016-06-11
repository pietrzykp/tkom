//
// Created by paulina on 06.06.16.
//

#ifndef TKOM2_BUILDEXPRESSION_H
#define TKOM2_BUILDEXPRESSION_H


#include <iostream>
#include "Expression.h"
#include "Value.h"

namespace pr {
    enum class EndFunction {
        Build,
        StaticLib
    };

    class BuildOrStaticExpression : public Expression {
        EndFunction function;
        std::shared_ptr<Value> result;
        std::shared_ptr<Value> files;
        std::shared_ptr<Value> flags;
    public:
        BuildOrStaticExpression(EndFunction f_, std::shared_ptr<Value> result_, std::shared_ptr<Value> files_, std::shared_ptr<Value> flags_)
                : function(f_), result(std::move(result_)), files(std::move(files_)), flags(std::move(flags_)) {};
        ~BuildOrStaticExpression() {};

        bool evaluate()  override { std::cout<<toString()<<std::endl;};
        std::string toString() const override;
    };

};
#endif //TKOM2_BUILDEXPRESSION_H
