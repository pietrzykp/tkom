//
// Created by paulina on 28.05.16.
//

#ifndef TKOM_CPPSCANNER_H
#define TKOM_CPPSCANNER_H

#include "Token.h"
#include <string>

class CppScanner {

public:
    CppScanner(std::istream& in);


    void readNextToken();
    Token getToken() const { return token; } ;
    void consumeLine();

private:
    bool tryEof();
    bool tryAlnum();

    bool tryStringToken();
    bool tryAnd();
    bool tryOperator();
    void getNextChar();

    void ignoreWhitespacesAndComment();
    void throwInvalidSyntax();
    void throwNoStringEnding();



    std::istream& in;
    Token token;
    std::string read;
    int lineNumber = 1;
};


#endif //TKOM_CPPSCANNER_H
