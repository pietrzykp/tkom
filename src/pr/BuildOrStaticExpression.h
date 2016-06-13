//
// Created by paulina on 06.06.16.
//

#ifndef TKOM2_BUILDEXPRESSION_H
#define TKOM2_BUILDEXPRESSION_H


#include <iostream>
#include <string>
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

        static std::unordered_map<std::string, int> dependencies;
        static std::vector<std::vector <int> > graph;
    public:
        BuildOrStaticExpression(EndFunction f_, std::shared_ptr<Value> result_, std::shared_ptr<Value> files_, std::shared_ptr<Value> flags_)
                : function(f_), result(std::move(result_)), files(std::move(files_)), flags(std::move(flags_)) {};
        ~BuildOrStaticExpression() {};

        bool evaluate()  override;
        std::string toString() const override;
        static bool dfs(int i, gi);
        static bool dfs2(int i, std::string& s);
        static std::string buildPoprerly();
        static std::string preparedfs();
    };

};
#endif //TKOM2_BUILDEXPRESSION_H
