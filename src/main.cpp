/*
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>
#include "CppScanner.h"
#include "Parser.h"
#include "Token.h"
#include <memory>

using namespace std;


int main() {
    std::ifstream fs;
    fs.open("buildProject");

    //std::istringstream i("if('a' == 'b') { var temp = 'aaa'; } else if('c' == 'd') { var temp = 'jjj'; var jou = 'aaa';}");
    //std::istringstream i("def jou(a,b) { var temp = 'aaa'; }");
    //std::istringstream i("for (o in jou, i in jou2) var temp = 'a'; ");

    //std::istringstream i("staticlib('header.a', ['aaa.a'], jou);");

    std::istringstream i("def buildWithFlags(outNames, inNames) { if(temp == 'aaa' || 'aaa' == 'aaa' && 'i' != i) { build(a,b); } } call buildWithFlags('aaa', 'bbb');");
                                 //"build(temp, 'main.o');");
    //std::istringstream i("var temp = 'false';");
    //std::istringstream i("var headerLibFiles = ['aaa.o', [jou]];");
    //std::istringstream i("build('hello', ['main.o', jou]);");
    //std::istringstream i("build(jou, [hello], 'flaga');");
    //std::istringstream i("staticlib('aaa', headerLibFiles);");
    //std::istringstream i("call buildwithflags([aaa, 'aaa'], [jou, [jou1, 'jou2']]);");
    //std::istringstream i("def builfwithflags(outNames, inNames) {} ");
    //std::istringstream i("if(temp == 'aaa' || 'bbb' == 'ccc' && ddd == 'i') {} else {}");
    //std::istringstream i("for (o in onames) {}");

std::istringstream ii("#komentarz \n"
                                 "var temp = 'aaa';\n"
                                 "var hello = 'false';\n"
                                 "var moduleFlags = '-Wall';\n"
                                 "var headerLibFiles = ['header.o', 'factorial.o'];\n"
                                 "build(hello, ['main.o', 'header.a']);\n");
                                 "staticlib('main.o', 'main.cpp', '-Wall');\n"
                                 "def buildWithFlags(outNames, inNames) {"
                                         "var i = 'ii';\n"
                                 "if(temp == 'aaa' || 'aaa' == 'aaa' && 'i' != i) {\n"
                                 "for(o in onames, i in inames) {\n"
                                 "build(o,i,moduleFlags);#komentarz\n"
                                 "}\n"
                                 "} else {\n"
                                 "for(o in outnames, i in names){\n"
                                 "build(o,i);\n"
                                 "}\n"
                                 "}\n"
                                 "}\n";

    std::istringstream iq("\nvar moduleFlags = '-Wall';\n"
                                 "\n"
                                 "var headerLibFiles = ['header.o', 'aaaaaa.txt', 'factoraal.o']; #komentarz2\n"
                                 "build('aaa', ['bbb', 'ccc']);\n"
                                 "build('bbb', ['ddd', 'eee']);\n"
                                 "build('ddd', ['ggg', 'uuu']);\n"
                                 "\n"
                                 "staticlib('header.a', headerLibFiles, moduleFlags);");

    Parser p(std::shared_ptr<CppScanner>(new CppScanner(iq)));
    try {
        std::shared_ptr<Expression> e = p.parse();
        cout<<e->evaluate()<<endl;
        std::string dupa = pr::BuildOrStaticExpression::preparedfs();
        cout<<dupa;
      //  system(dupa.c_str());

    } catch(std::runtime_error err) {
        cout<<"ERROR: " << err.what();
    }
    return 0;
}
*/
