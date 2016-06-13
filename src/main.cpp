#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include "CppScanner.h"
#include "Parser.h"
#include "Token.h"
#include "GraphNode.h"
#include <memory>

using namespace std;


int main() {
    std::ifstream fs;
    fs.open("buildProject");

    Parser p(std::shared_ptr<CppScanner>(new CppScanner(fs)));
    try {
        std::shared_ptr<Expression> e = p.parse();
        cout<<e->evaluate()<<endl;
        std::string result = Resolver::resolve();
        system(result.c_str());

    } catch(std::runtime_error err) {
        cout<<"ERROR: " << err.what();
    }
    return 0;
}
