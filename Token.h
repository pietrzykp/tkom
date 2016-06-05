//
// Created by paulina on 10.05.16.
//

#ifndef TKOM_TOKEN_H
#define TKOM_TOKEN_H

#include <string>
#include <iostream>
class Token {

public:
    enum Type {
        VAR, IN, IF, ELSE, DEF, CALL, BUILD, STATICLIB,
        ASSIGN_OPER, AND_OPER, OR_OPER, EQUAL_OPER, NOT_EQUAL_OPER,
        SEMICOLON, COMMA,
        SQUARE_BRACKET_LEFT, SQUARE_BRACKET_RIGHT,
        ROUND_BRACKET_LEFT, ROUND_BRACKET_RIGHT,
        CURLY_BRACKET_LEFT, CURLY_BRACKET_RIGHT,
        PARAMETER, IDENTIFIER, STRING, EOF_IDENT, ERROR
    };
    Token(std::string s, Token::Type t) {type = t; content = s; };
    Token() : type(Type::ERROR) {} ;
    Type getType() const { return type; };
    std::string getContent() const { return content; };

private:
    Type type;
    std::string content;

};



#endif //TKOM_TOKEN_H
