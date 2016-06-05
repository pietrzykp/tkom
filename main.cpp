#include <stdexcept>
#include <fstream>
#include <sstream>
#include "CppScanner.h"
#include "Parser.h"
#include <memory>

using namespace std;

int main() {
    std::ifstream fs;
    fs.open("buildProjectBad");

    //std::istringstream i("if('a' == 'b') { var temp = 'aaa'; } else if('c' == 'd') { var temp = 'jjj'; var jou = 'aaa';}");
    std::istringstream i("call jou(['aaa', 'bbb'], ['ccc']);");

    Parser p(std::unique_ptr<CppScanner>(new CppScanner(i)));
    std::unique_ptr<Expression> e = p.parse();

     cout<<e->evaluate()<<endl<<e->toString();

    return 0;
}