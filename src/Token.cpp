//
// Created by paulina on 10.05.16.
//

#include "Token.h"


//Token::Token(std::string s, Token::Type t) : content(s), type(t) {};
std::string Token::toString() const {
    const Token::Type t = getType();
    return toString(t) != getContent() ? toString(t) + " " + getContent() : toString(t);
}

std::string Token::toString(Token::Type type){
    switch(type) {
        case Type::ROUND_BRACKET_RIGHT : return ")";
        case Type::ROUND_BRACKET_LEFT: return "(";
        case Type::AND_OPER: return "&&";
        case Type::ASSIGN_OPER: return "=";
        case Type::BUILD: return "build";
        case Type::CALL: return "call";
        case Type::COMMA: return ",";
        case Type::CURLY_BRACKET_LEFT: return "{";
        case Type::CURLY_BRACKET_RIGHT: return "}";
        case Type::DEF: return "def";
        case Type::ELSE: return "else";
        case Type::EOF_IDENT: return "end of file";
        case Type::EQUAL_OPER: return "==";
        case Type::ERROR: return "error";
        case Type::FOR: return "for";
        case Type::IDENTIFIER: return "identifier";
        case Type::IF: return "if";
        case Type::IN: return "in";
        case Type::NOT_EQUAL_OPER: return "!=";
        case Type::OR_OPER: return "||";
        case Type::SEMICOLON: return ";";
        case Type::SQUARE_BRACKET_LEFT:return "[";
        case Type::STATICLIB:return "staticlib";
        case Type::SQUARE_BRACKET_RIGHT:return "]";
        case Type::STRING:return "string";
        case Type::VAR:return "var";
        default: return "undefined token";
    }
}



