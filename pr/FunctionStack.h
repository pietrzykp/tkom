//
// Created by paulina on 10.06.16.
//

#ifndef TKOM2_FUNCTIONSTACK_H
#define TKOM2_FUNCTIONSTACK_H

#include <string>
#include <bits/unique_ptr.h>
#include "FunctionDeclaration.h"

namespace pr {

    class FunctionStack {
    public:
        static std::vector<std::shared_ptr<FunctionDeclaration> > decl;
        static bool executeFunction(std::string label, std::vector<std::shared_ptr <Value>> values) {
            for(int i = 0; i < decl.size(); ++i) {
                if(decl[i]->getLabel() == label) {
                    decl[i]->execute(values);
                }
            }
            return true;
        }
    };
}


#endif //TKOM2_FUNCTIONSTACK_H
