#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include "CppScanner.h"
#include "Parser.h"
#include "GraphNode.h"
#include <cstring>

using namespace std;


int main(int argc, char *argv[]) {
    std::ifstream fs;
    fs.open("buildProject");
    bool execute = !(argc == 2 && !strcmp(argv[1], "-noexecute"));
    Parser p(std::shared_ptr<CppScanner>(new CppScanner(fs)));
    try {
        std::shared_ptr<Expression> e = p.parse();
        e->evaluate();
        std::string result = Resolver::resolve();
        if(execute)
            system(result.c_str());
        else
            cout<<result<<endl;
    } catch(std::runtime_error err) {
        cout<<"ERROR: " << err.what();
    }
    return 0;
}
