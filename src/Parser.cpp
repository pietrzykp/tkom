//
// Created by paulina on 03.06.16.
//

#include "Parser.h"
#include "pr/Value.h"
#include "pr/CompExpression.h"
#include "pr/AndExpression.h"
#include "pr/OrExpression.h"
#include "pr/VariableDeclaration.h"
#include "pr/Expressions.h"
#include "pr/IfExpression.h"
#include "pr/FunctionCall.h"
#include "pr/FunctionDeclaration.h"
#include "pr/ForExpression.h"
#include <sstream>

using std::string;
Parser::Parser(std::shared_ptr<CppScanner> sc) : scanner(std::move(sc)) {}


std::shared_ptr<Expression> Parser::parse() {
    Token t;
    do {
        try {
            scanner->readNextToken();
            t = scanner->getToken();
            readTokens.push_back(t);
        } catch(std::runtime_error err) {
            scanner->consumeLine();
            unparsable = true;
            throw(err);
        }
    } while ( t.getType() != Token::Type::EOF_IDENT);
    if(unparsable)
        return nullptr;
    return readExpressions();
}

std::shared_ptr<Expression> Parser::readExpressions() {
    std::vector<std::shared_ptr<Expression> > expressions;
    while(!checkTokenType(Token::Type::EOF_IDENT)) {
        expressions.push_back(std::move(readExpression()));
    }
    return std::shared_ptr<Expressions>(new Expressions(std::move(expressions)));
}

std::shared_ptr<Expression> Parser::readExpression() {
    Token token = getToken();
    switch (token.getType()) {
        case Token::Type::IF :
            getNextToken();
            return readIfExpression();
        case Token::Type::VAR :
            return readVariableDeclaration();
        case Token::Type::CALL :
            return readFunctionCall();
        case Token::Type::DEF:
            return readFunctionDeclaration();
        case Token::Type::FOR:
            return readForExpression();
        case Token::Type::BUILD:
            return readBuildExpression();
        case Token::Type::STATICLIB:
            return readStaticExpression();
        default:
            throwUnexpextedToken(Token::Type::VAR);
    }
}

Token Parser::requireToken(Token::Type expectedType) {
    auto token = getToken();
    auto type = token.getType();
    if(type != expectedType)
        throwUnexpextedToken(expectedType);
    return token;
}


Token Parser::getNextToken() {
    return readTokens[index++];
}

Token Parser::getToken() {
    return readTokens[index];
}

bool Parser::checkTokenType(Token::Type type) const {
    return readTokens[index].getType() == type;
}

std::shared_ptr<IfExpression> Parser::readIfExpression() {
    requireToken(Token::Type::ROUND_BRACKET_LEFT);
    getNextToken();
    std::shared_ptr<Expression> expr = readCompOrInsideIf();
    expr = readAndExpression(std::move(expr));
    expr = readOrExpression(std::move(expr));
    requireToken(Token::Type::ROUND_BRACKET_RIGHT);
    getNextToken();

    std::shared_ptr<Expressions> expressions;
    std::shared_ptr<IfExpression> elseExpr = nullptr;

    bool additionalBracket = checkTokenType(Token::Type::CURLY_BRACKET_LEFT);
    expressions = getBracketExpressions();

    if(additionalBracket) {
        if (checkTokenType(Token::Type::CURLY_BRACKET_RIGHT))
            getNextToken();
        else
            throwUnexpextedToken(Token::Type::CURLY_BRACKET_RIGHT);
    }

    if(checkTokenType(Token::Type::ELSE)) {
        getNextToken();
        if(checkTokenType(Token::Type::IF)) {
            getNextToken();
            elseExpr = readIfExpression();
        } else {
            additionalBracket = checkTokenType(Token::Type::CURLY_BRACKET_LEFT);
            std::shared_ptr<Expressions> bracket = getBracketExpressions();
            if(additionalBracket) {
                if (checkTokenType(Token::Type::CURLY_BRACKET_RIGHT))
                    getNextToken();
                else
                    throwUnexpextedToken(Token::Type::CURLY_BRACKET_RIGHT);
            }
            elseExpr = std::shared_ptr<IfExpression>(new IfExpression(nullptr, std::move(bracket), nullptr));
        }
    }
    return std::shared_ptr<IfExpression>(new IfExpression(std::move(expr), std::move(expressions), std::move(elseExpr)));
}


std::shared_ptr<Expressions> Parser::getBracketExpressions(){
    std::vector<std::shared_ptr<Expression> > expressions;
    if(checkTokenType(Token::Type::CURLY_BRACKET_LEFT)) {
        getNextToken();
        while(!checkTokenType(Token::Type::CURLY_BRACKET_RIGHT)) {
            expressions.push_back(std::move(readExpression()));
        }
    } else {
        expressions.push_back(std::move(readExpression()));
    }
    return std::shared_ptr<Expressions>(new Expressions(std::move(expressions)));
}

std::shared_ptr<Expression> Parser::readVariableDeclaration() {
    getNextToken();
    requireToken(Token::Type::IDENTIFIER);
    string label = getToken().getContent();
    getNextToken();
    requireToken(Token::Type::ASSIGN_OPER);
    getNextToken();
    std::shared_ptr<Value> val = readRecursiveValue();
    getNextToken();
    requireToken(Token::Type::SEMICOLON);
    getNextToken();
    return std::shared_ptr<VariableDeclaration>(new VariableDeclaration(label, std::move(val)));
}

std::shared_ptr<Expression> Parser::readFunctionDeclaration() {
    getNextToken();
    requireToken(Token::Type::IDENTIFIER);
    string label = getToken().getContent();
    getNextToken();
    requireToken(Token::Type::ROUND_BRACKET_LEFT);
    std::vector<string> paramsNames;
    getNextToken();
    if(!checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        readFunctionHelper(paramsNames);
    }
    while(!checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        requireToken(Token::Type::COMMA);
        getNextToken();
        readFunctionHelper(paramsNames);
    }
    getNextToken();
    requireToken(Token::Type::CURLY_BRACKET_LEFT);
    std::shared_ptr<Expressions> expressions = getBracketExpressions();
    requireToken(Token::Type::CURLY_BRACKET_RIGHT);
    getNextToken();
    return std::shared_ptr<FunctionDeclaration>(new FunctionDeclaration(label, paramsNames, std::move(expressions)));
}

void Parser::readFunctionHelper(std::vector<std::string> & paramsNames) {
    requireToken(Token::Type::IDENTIFIER);
    paramsNames.push_back(getToken().getContent());
    getNextToken();
}

std::shared_ptr<Expression> Parser::readForExpression() {
    getNextToken();
    requireToken(Token::Type::ROUND_BRACKET_LEFT);
    getNextToken();
    std::vector<std::string> paramNames;
    std::vector<std::shared_ptr<Value> > lists;
    if(!checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        readForHelper(paramNames, lists);
    }
    while(!checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        requireToken(Token::Type::COMMA);
        getNextToken();
        readForHelper(paramNames, lists);
    }
    getNextToken();
    std::shared_ptr<Expressions> expressions = getBracketExpressions();
    getNextToken();
    return std::shared_ptr<ForExpression>(new ForExpression(paramNames, std::move(lists), std::move(expressions)));
}

void Parser::readForHelper(std::vector<std::string> & paramNames, std::vector<std::shared_ptr<Value> > & lists) {
    requireToken(Token::Type::IDENTIFIER);
    std::string name = getToken().getContent();
    getNextToken();
    requireToken(Token::Type::IN);
    getNextToken();
    std::shared_ptr<Value> value = readNonRecursiveValue(getToken());
    paramNames.push_back(name);
    lists.push_back(std::move(value));
    getNextToken();
}

std::shared_ptr<Expression> Parser::readFunctionCall() {
    getNextToken();
    requireToken(Token::Type::IDENTIFIER);
    string label = getToken().getContent();
    getNextToken();
    requireToken(Token::Type::ROUND_BRACKET_LEFT);
    getNextToken();
    std::vector<std::shared_ptr<Value> > values;
    if(!checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        readCallHelper(values);
    }
    while(!checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        requireToken(Token::Type::COMMA);
        getNextToken();
        readCallHelper(values);
    }
    getNextToken();
    requireToken(Token::Type::SEMICOLON);
    getNextToken();
    return std::shared_ptr<FunctionCall>(new FunctionCall(label, std::move(values)));
}

void Parser::readCallHelper(std::vector<std::shared_ptr<Value> > &  values) {
    std::shared_ptr<Value> val = readRecursiveValue();
    values.push_back(std::move(val));
    getNextToken();
}

std::shared_ptr<Expression> Parser::readOrExpression(std::shared_ptr<Expression> expr) {
    if(checkTokenType(Token::Type::OR_OPER)) {
        while(checkTokenType(Token::Type::OR_OPER)) {
            getNextToken();
            std::shared_ptr<Expression> expr2 = readCompOrInsideIf();
            expr2 = readAndExpression(std::move(expr2));
            expr = std::shared_ptr<OrExpression>(new OrExpression(std::move(expr), std::move(expr2)));
        }
        return expr;
    } else if(checkTokenType(Token::Type::AND_OPER) || checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        return std::shared_ptr<OrExpression>(new OrExpression(std::move(expr), nullptr));
    }
    throwUnexpextedToken(Token::Type::OR_OPER);
}

std::shared_ptr<Expression> Parser::readAndExpression(std::shared_ptr<Expression> expr) {
    if(checkTokenType(Token::Type::AND_OPER)) {
        while(checkTokenType(Token::Type::AND_OPER)) {
            getNextToken();
            std::shared_ptr<Expression> expr2  = readCompOrInsideIf();
            expr = std::shared_ptr<AndExpression>(new AndExpression(std::move(expr), std::move(expr2)));
        }
        return expr;
    } else if(checkTokenType(Token::Type::OR_OPER) || checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        return std::shared_ptr<AndExpression>(new AndExpression(std::move(expr), nullptr));
    }
    throwUnexpextedToken(Token::Type::AND_OPER);
}


std::shared_ptr<Value> Parser::readNonRecursiveValue(Token token) {
    switch(token.getType()) {
        case Token::Type::STRING:
            return std::shared_ptr<Value>(new Value(token.getContent(), false));
        case Token::Type::PARAMETER:
        case Token::Type::IDENTIFIER:
            return std::shared_ptr<Value>(new Value(token.getContent(), true));
        case Token::Type::SQUARE_BRACKET_LEFT:
            std::vector<std::shared_ptr<Value> > valVector;
            while(!checkTokenType(Token::Type::SQUARE_BRACKET_RIGHT)) {
                getNextToken();
                std::shared_ptr<Value> val = readRecursiveValue();
                if(!val->isSingleValue())
                    throwUnexpextedToken(Token::Type::STRING);
                valVector.push_back(std::move(val));
                getNextToken();
                if(!checkTokenType(Token::Type::SQUARE_BRACKET_RIGHT) && !checkTokenType(Token::Type::COMMA))
                    throwUnexpextedToken(Token::Type::SQUARE_BRACKET_RIGHT);
            }
            return std::shared_ptr<Value>(new Value(std::move(valVector)));
    }
    throwUnexpextedToken(Token::Type::STRING);
}

std::shared_ptr<Value> Parser::readNonArray(Token token) {
    switch(token.getType()) {
        case Token::Type::STRING:
            return std::shared_ptr<Value>(new Value(token.getContent(), false));
        case Token::Type::PARAMETER:
        case Token::Type::IDENTIFIER:
            return std::shared_ptr<Value>(new Value(token.getContent(), true));
    }
    throwUnexpextedToken(Token::Type::STRING);
}

std::shared_ptr<Value> Parser::readRecursiveValue() {
    Token token = getToken();
    switch(token.getType()) {
        case Token::Type::STRING:
            return std::shared_ptr<Value>(new Value(token.getContent(), false));
        case Token::Type::PARAMETER:
        case Token::Type::IDENTIFIER:
            return std::shared_ptr<Value>(new Value(token.getContent(), true));
        case Token::Type::SQUARE_BRACKET_LEFT:
            std::vector<std::shared_ptr<Value> > valVector;
            while(!checkTokenType(Token::Type::SQUARE_BRACKET_RIGHT)) {
                getNextToken();
                std::shared_ptr<Value> val = readRecursiveValue();
                getNextToken();
                if(!checkTokenType(Token::Type::SQUARE_BRACKET_RIGHT) && !checkTokenType(Token::Type::COMMA))
                    throwUnexpextedToken(Token::Type::SQUARE_BRACKET_RIGHT);
                valVector.push_back(std::move(val));
            }
            return std::shared_ptr<Value>(new Value(std::move(valVector)));
    }
    throwUnexpextedToken(Token::Type::STRING);
}

Operator Parser::readCompOperator(Token token) {
    switch(token.getType()) {
        case Token::Type::EQUAL_OPER:
            return Operator::Equal;
        case Token::Type::NOT_EQUAL_OPER:
            return Operator::NotEqual;
    }
    throwUnexpextedToken(Token::Type::EQUAL_OPER);
}

std::shared_ptr<Expression> Parser::readCompOrInsideIf() {
    if(checkTokenType(Token::Type::ROUND_BRACKET_LEFT))
            return readIfExpression();
    else {
        std::shared_ptr<Value> val = readNonArray(getNextToken());
        const auto oper = readCompOperator(getNextToken());
        std::shared_ptr<Value> val2 = readNonArray(getNextToken());
        return std::shared_ptr<CompExpression>(new CompExpression(std::move(val), oper, std::move(val2)));
    }
}

std::shared_ptr<Expression> Parser::readBuildExpression() {
    return readBuildOrStaticExpression(EndFunction::Build);
}

std::shared_ptr<Expression> Parser::readStaticExpression() {
    return readBuildOrStaticExpression(EndFunction::StaticLib);
}

std::shared_ptr<Expression> Parser::readBuildOrStaticExpression(EndFunction f) {
    getNextToken();
    requireToken(Token::Type::ROUND_BRACKET_LEFT);
    getNextToken();
    std::shared_ptr<Value> result = readNonArray(getToken());
    getNextToken();
    requireToken(Token::Type::COMMA);
    getNextToken();
    std::shared_ptr<Value> files = readNonRecursiveValue(getToken());
    getNextToken();
    std::shared_ptr<Value> flags = nullptr;
    if(checkTokenType(Token::Type::COMMA)) {
        getNextToken();
        flags = readNonRecursiveValue(getToken());
        getNextToken();
    }
    requireToken(Token::Type::ROUND_BRACKET_RIGHT);
    getNextToken();
    requireToken(Token::Type::SEMICOLON);
    getNextToken();
    return std::shared_ptr<BuildOrStaticExpression>
            (new BuildOrStaticExpression(f, std::move(result), std::move(files), std::move(flags)));
}

void Parser::throwUnexpextedToken(Token::Type expected) {
    std::ostringstream os;
    os<<getToken().getLine();
    throw std::runtime_error("Line " + os.str() + ": Unexpected token: '" + getToken().toString()
                                 + "', expecting (among others) : '" + Token::toString(expected) + "' ");
}























