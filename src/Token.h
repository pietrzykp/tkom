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
        VAR, FOR, IN, IF, ELSE, DEF, CALL, BUILD, STATICLIB,
        ASSIGN_OPER, AND_OPER, OR_OPER, EQUAL_OPER, NOT_EQUAL_OPER,
        SEMICOLON, COMMA,
        SQUARE_BRACKET_LEFT, SQUARE_BRACKET_RIGHT,
        ROUND_BRACKET_LEFT, ROUND_BRACKET_RIGHT,
        CURLY_BRACKET_LEFT, CURLY_BRACKET_RIGHT,
        IDENTIFIER, STRING, EOF_IDENT, ERROR
    };
    Token(std::string s, Token::Type t, int lineN) {type = t; content = s; line = lineN;};
    Token() : type(Type::ERROR) {} ;
    Type getType() const { return type; };
    std::string getContent() const { return content; };
    std::string toString() const;
    static std::string toString(Token::Type type);
    int getLine() {return line;};

private:
    Type type;
    std::string content;
    int line;
};



#endif //TKOM_TOKEN_H
