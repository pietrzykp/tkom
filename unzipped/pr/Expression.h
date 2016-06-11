//
// Created by paulina on 03.06.16.
//

#ifndef TKOM2_EXPRESSION_H
#define TKOM2_EXPRESSION_H
#include <string>

namespace pr {
    class Expression {
    public:
        virtual ~Expression() {};

        virtual bool evaluate() const = 0;
        virtual std::string toString() const = 0;
    };
}


#endif //TKOM2_EXPRESSION_H
