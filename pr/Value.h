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
    class Value : public std::enable_shared_from_this<Value> {
        std::vector<std::shared_ptr<Value> > arrayValue;
        std::string value;
        bool searchValue;
        bool singleValue;
    public:
        Value(std::vector<std::shared_ptr<Value> > val_)
                : arrayValue(std::move(val_)), searchValue(false), singleValue(false) {};
        Value(std::string val_, bool search_) :
            value(val_), searchValue(search_), singleValue(true) {};
        std::string toString();
        int getSize() {
            if(singleValue)
                return 1;
            return arrayValue.size();
        }
        std::string getSingleValue();
        std::shared_ptr<Value> getNonSearchValue();

        void getAllValues(std::vector<std::string> & vec);

        std::shared_ptr<Value> getByIndex(int index);
        bool isSingleValue() { return singleValue; };
        ~Value() {};
    };
}


#endif //TKOM2_VALUE_H
