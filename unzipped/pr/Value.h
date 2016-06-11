//
// Created by paulina on 04.06.16.
//

#ifndef TKOM2_VALUE_H
#define TKOM2_VALUE_H
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

namespace pr {
    class Value {
        std::vector<std::shared_ptr<Value> > arrayValue;
        std::string value;
        bool searchValue;
        bool singleValue;
    public:
        Value(std::vector<std::shared_ptr<Value> > val_)
                : arrayValue(std::move(val_)), searchValue(false), singleValue(false) {};
        Value(std::string val_, bool search_) :
            value(val_), searchValue(search_), singleValue(true) {};
        std::string getValue();
        std::string toString();
        bool isSingleValue() { return singleValue; };
    };
}

extern std::unordered_map<std::string, std::shared_ptr<pr::Value>> variables;

#endif //TKOM2_VALUE_H
