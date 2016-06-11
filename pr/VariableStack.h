//
// Created by paulina on 10.06.16.
//

#ifndef TKOM2_VARIABLESTACK_H
#define TKOM2_VARIABLESTACK_H

#include <vector>
#include <iostream>
#include "Value.h"
#include "Expression.h"

namespace pr {

    struct VariableDef {
        std::shared_ptr<Value> value;
        std::string label;
        int level;

        VariableDef(std::shared_ptr<pr::Value> value_, int level_, std::string label_) : value(value_), label(label_),
                                                                                         level(level_) { };
    };

    class VariableStack {
        static int level;
        static std::vector <VariableDef> variables;
    public:
        static void putValue(std::shared_ptr<pr::Value> value, std::string label) {
            std::cout<<label<<" "<<value->getSize()<<std::endl;
            variables.push_back(VariableDef(value, level, label));
        }
        static std::shared_ptr<Value> getValue(std::string label) {
            for(int i = variables.size()-1; i >= 0; --i) {
                if(variables[i].label == label)
                    return variables[i].value;
            }
            return nullptr;
        }
        static void raiseLevel() {
            ++level;
        }
        static void lowerLevel() {
            --level;
            while(variables[variables.size()-1].level > level)
                variables.pop_back();
        }
    };
}


#endif //TKOM2_VARIABLESTACK_H
