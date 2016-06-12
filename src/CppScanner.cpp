//
// Created by paulina on 28.05.16.
//

#include "CppScanner.h"
#include "Token.h"
#include <istream>
#include <unordered_map>
#include <sstream>

using namespace std;
CppScanner::CppScanner(std::istream& in_) : in(in_) { }

typedef std::unordered_map<std::string,Token::Type > stringmap;

stringmap tokenMap { {"build",   Token::Type::BUILD},  //  0
                     {"var", Token::Type::VAR},  //  1
                     {"in",  Token::Type::IN},  //  2
                     {"if",  Token::Type::IF},  //  3
                     {"def", Token::Type::DEF},  //  4
                     {"staticlib",   Token::Type::STATICLIB},  //  5
                     {"else",    Token::Type::ELSE},
                     { "call", Token::Type::CALL },
                     {"for", Token::Type::FOR}};

void CppScanner::readNextToken() {
    ignoreWhitespacesAndComment();
    read = "";
    if(tryEof()) {
        token = Token("", Token::Type::EOF_IDENT , lineNumber);
        return;
    }
    if(tryStringToken()) //
        return;
    if(tryParameterOrAnd())
        return;
    if(tryOperator())
        return;
    if(tryAlnum()) //
        return;
    throwInvalidSyntax();
}

bool CppScanner::tryAlnum() {
    while(in && std::isalnum(in.peek())) {
        getNextChar();
    }
    if(read == "")
        return false;
    try {
        Token::Type type = tokenMap.at(read);
        token = Token(read, type, lineNumber);
    } catch (...){
        token = Token(read, Token::Type::IDENTIFIER, lineNumber);
    }
    return true;

}

void CppScanner::ignoreWhitespacesAndComment() {
    while(in && (std::isspace(in.peek()) || in.peek() == '#' )) {
        while (in && std::isspace(in.peek()))
            getNextChar();
        while (in && in.peek() == '#') {
            getNextChar();
            while (in && in.peek() != '\n')
                getNextChar();
            if(in)
                getNextChar();
        }
    }
}

bool CppScanner::tryParameterOrAnd() {
    if(in && in.peek() == '&') {
        getNextChar();
        if(in && in.peek() == '&') {
            getNextChar();
            token = Token("&&", Token::Type::AND_OPER, lineNumber);
            return true;
        }
        if(!isdigit(in.peek()))
            throwInvalidSyntax();
        while(in && std::isdigit(in.peek()))
            getNextChar();
        if(std::isalnum(in.peek())|| in.peek() == '\'')
            throwInvalidSyntax();
        token = Token(read, Token::Type::PARAMETER, lineNumber);
        return true;
    }
}

bool CppScanner::tryEof()
{
    if (!in.eof())
        return false;
    return true;
}

bool CppScanner::tryStringToken() {
    if(in && in.peek() == '\'') {
        getNextChar();
        read = "";
        bool escape = false;
        while(in && !(in.peek() == '\'' && !escape)) {
            if(in.peek() == '\\' && !escape)
                escape = true;
            else {
                escape = false;
            }
            if(in.peek() == '\n') {
                throwNoStringEnding();
            }
            if(escape)
                in.get();
            else
                getNextChar();
        }
        if(!in)
            throwNoStringEnding();
        token = Token(read, Token::Type::STRING, lineNumber);
        getNextChar();
        return true;
    }
    return false;
}

bool CppScanner::tryOperator() {
    char c = in.peek();
    switch(c) {
        case '!': getNextChar();
            c = in.peek();
            if(c=='=') { getNextChar(); token = Token("!=", Token::Type::NOT_EQUAL_OPER, lineNumber);}
            else {
                throwInvalidSyntax();
            }
            break;
        case '|': getNextChar();
            c = in.peek();
            if(c=='|') { getNextChar(); token = Token("||", Token::Type::OR_OPER, lineNumber) ;}
            else {
                throwInvalidSyntax();
            }
            break;
        case '=': getNextChar();
            c = in.peek();
            if(c=='=') { getNextChar(); token = Token("==", Token::Type::EQUAL_OPER, lineNumber); }
            else {
                token = Token("=", Token::Type::ASSIGN_OPER, lineNumber) ;
            }
            break;
        case ';': getNextChar(); token = Token(";", Token::Type::SEMICOLON, lineNumber); break;
        case ',': getNextChar(); token = Token(",", Token::Type::COMMA, lineNumber); break;
        case '[': getNextChar(); token = Token("[", Token::Type::SQUARE_BRACKET_LEFT, lineNumber); break;
        case ']': getNextChar(); token = Token("]", Token::Type::SQUARE_BRACKET_RIGHT, lineNumber); break;
        case '(': getNextChar(); token = Token("(", Token::Type::ROUND_BRACKET_LEFT, lineNumber); break;
        case ')': getNextChar(); token = Token(")", Token::Type::ROUND_BRACKET_RIGHT, lineNumber); break;
        case '{': getNextChar(); token = Token("{", Token::Type::CURLY_BRACKET_LEFT, lineNumber); break;
        case '}': getNextChar(); token = Token("}", Token::Type::CURLY_BRACKET_RIGHT, lineNumber); break;
        default: return false;
    }
    return true;
}

void CppScanner::getNextChar() {
    char c = in.get();
    if(c == '\n')
        ++lineNumber;
    read += static_cast<char>(c);
}

void CppScanner::throwInvalidSyntax()
{
    const std::string msg = "Unknown token, starting with: ";
    ostringstream i;
    i << lineNumber;
    throw std::runtime_error("Line" + i.str() + " - " + msg + static_cast<char>(read[read.size()-1]));
}


void CppScanner::throwNoStringEnding() {
    const std::string msg = "No string ending";
    ostringstream i;
    i << lineNumber;
    throw std::runtime_error("Line" + i.str() + " - " + msg);
}

void CppScanner::consumeLine() {
    while(in && in.get() != '\n');
    ++lineNumber;
}