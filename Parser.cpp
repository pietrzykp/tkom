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

using std::string;
Parser::Parser(std::unique_ptr<CppScanner> sc) : scanner(std::move(sc)) {}


std::unique_ptr<Expression> Parser::parse() {
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

std::unique_ptr<Expression> Parser::readExpressions() {
    std::vector<std::unique_ptr<Expression> > expressions;
    while(!checkTokenType(Token::Type::EOF_IDENT)) {
        expressions.push_back(std::move(readExpression()));
    }
    return std::unique_ptr<Expressions>(new Expressions(std::move(expressions)));
}

std::unique_ptr<Expression> Parser::readExpression() {
    Token token = getToken();
    switch (token.getType()) {
        case Token::Type::IF :
            getNextToken();
            return readIfExpression();
        case Token::Type::VAR :
            return readVariableDelaration();
        case Token::Type::CALL :
            return readFunctionCall();
       /* case Token::Type::*/
    }
}

Token Parser::requireToken(Token::Type expectedType) {
    auto token = getToken();
    auto type = token.getType();
    if(type != expectedType)
        throwUnexpextedToken();
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

std::unique_ptr<IfExpression> Parser::readIfExpression() {
    requireToken(Token::Type::ROUND_BRACKET_LEFT);
    getNextToken();
    std::unique_ptr<Expression> expr = readCompOrInsideIf();
    expr = readAndExpression(std::move(expr));
    expr = readOrExpression(std::move(expr));
    requireToken(Token::Type::ROUND_BRACKET_RIGHT);
    getNextToken();

    std::unique_ptr<Expressions> expressions;
    std::unique_ptr<IfExpression> elseExpr = nullptr;

    bool additionalBracket = checkTokenType(Token::Type::CURLY_BRACKET_LEFT);
    expressions = getBracketExpressions();

    if(additionalBracket) {
        if (checkTokenType(Token::Type::CURLY_BRACKET_RIGHT))
            getNextToken();
        else
            throwUnexpextedToken();
    }

    if(checkTokenType(Token::Type::ELSE)) {
        getNextToken();
        if(checkTokenType(Token::Type::IF)) {
            getNextToken();
            elseExpr = readIfExpression();
        } else {
            elseExpr = std::unique_ptr<IfExpression>(new IfExpression(nullptr, getBracketExpressions(), nullptr));
        }
    }
    return std::unique_ptr<IfExpression>(new IfExpression(std::move(expr), std::move(expressions), std::move(elseExpr)));
}

std::unique_ptr<Expressions> Parser::getBracketExpressions(){
    std::vector<std::unique_ptr<Expression> > expressions;
    if(checkTokenType(Token::Type::CURLY_BRACKET_LEFT)) {
        getNextToken();
        while(!checkTokenType(Token::Type::CURLY_BRACKET_RIGHT)) {
            expressions.push_back(std::move(readExpression()));
        }
    } else {
        expressions.push_back(std::move(readExpression()));
    }
    return std::unique_ptr<Expressions>(new Expressions(std::move(expressions)));
}

std::unique_ptr<Expression> Parser::readVariableDelaration() {
    getNextToken();
    requireToken(Token::Type::IDENTIFIER);
    string label = getToken().getContent();
    getNextToken();
    requireToken(Token::Type::ASSIGN_OPER);
    getNextToken();
    std::unique_ptr<Value> val = readRecursiveValue();
    getNextToken();
    requireToken(Token::Type::SEMICOLON);
    getNextToken();
    return std::unique_ptr<VariableDeclaration>(new VariableDeclaration(label, std::move(val)));
}

std::unique_ptr<Expression> Parser::readFunctionCall() {
    getNextToken();
    requireToken(Token::Type::IDENTIFIER);
    string label = getToken().getContent();
    getNextToken();
    requireToken(Token::Type::ROUND_BRACKET_LEFT);
    getNextToken();
    std::vector<std::unique_ptr<Value> > values;
    if(!checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        std::unique_ptr<Value> val = readRecursiveValue();
        values.push_back(std::move(val));
        getNextToken();
    }
    while(!checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        requireToken(Token::Type::COMMA);
        getNextToken();
        std::unique_ptr<Value> val = readRecursiveValue();
        values.push_back(std::move(val));
        getNextToken();
    }
    getNextToken();
    requireToken(Token::Type::SEMICOLON);
    getNextToken();
    return std::unique_ptr<FunctionCall>(new FunctionCall(label, std::move(values)));
}

std::unique_ptr<Expression> Parser::readOrExpression(std::unique_ptr<Expression> expr) {
    if(checkTokenType(Token::Type::OR_OPER)) {
        while(checkTokenType(Token::Type::OR_OPER)) {
            getNextToken();
            std::unique_ptr<Expression> expr2 = readCompOrInsideIf();
            expr2 = readAndExpression(std::move(expr2));
            expr = std::unique_ptr<OrExpression>(new OrExpression(std::move(expr), std::move(expr2)));
        }
        return expr;
    } else if(checkTokenType(Token::Type::AND_OPER) || checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        return std::unique_ptr<OrExpression>(new OrExpression(std::move(expr), nullptr));
    }
    throwUnexpextedToken();
}

std::unique_ptr<Expression> Parser::readAndExpression(std::unique_ptr<Expression> expr) {
    if(checkTokenType(Token::Type::AND_OPER)) {
        while(checkTokenType(Token::Type::AND_OPER)) {
            getNextToken();
            std::unique_ptr<Expression> expr2  = readCompOrInsideIf();
            expr = std::unique_ptr<AndExpression>(new AndExpression(std::move(expr), std::move(expr2)));
        }
        return expr;
    } else if(checkTokenType(Token::Type::OR_OPER) || checkTokenType(Token::Type::ROUND_BRACKET_RIGHT)) {
        return std::unique_ptr<AndExpression>(new AndExpression(std::move(expr), nullptr));
    }
    throwUnexpextedToken();
}


std::unique_ptr<Value> Parser::readIfValue(Token token) {
    switch(token.getType()) {
        case Token::Type::STRING:
            return std::unique_ptr<Value>(new Value(token.getContent(), false));
        case Token::Type::PARAMETER:
        case Token::Type::IDENTIFIER:
            return std::unique_ptr<Value>(new Value(token.getContent(), true));
    }
    throwUnexpextedToken();
}

std::unique_ptr<Value> Parser::readRecursiveValue() {
    Token token = getToken();
    switch(token.getType()) {
        case Token::Type::STRING:
            return std::unique_ptr<Value>(new Value(token.getContent(), false));
        case Token::Type::PARAMETER:
        case Token::Type::IDENTIFIER:
            return std::unique_ptr<Value>(new Value(token.getContent(), true));
        case Token::Type::SQUARE_BRACKET_LEFT:
            std::vector<std::unique_ptr<Value> > valVector;
            while(!checkTokenType(Token::Type::SQUARE_BRACKET_RIGHT)) {
                getNextToken();
                std::unique_ptr<Value> val = readRecursiveValue();
                getNextToken();
                if(!checkTokenType(Token::Type::SQUARE_BRACKET_RIGHT) && !checkTokenType(Token::Type::COMMA))
                    throwUnexpextedToken();
                valVector.push_back(std::move(val));
            }
            return std::unique_ptr<Value>(new Value(std::move(valVector)));
    }
    throwUnexpextedToken();
}

Operator Parser::readCompOperator(Token token) {
    switch(token.getType()) {
        case Token::Type::EQUAL_OPER:
            return Operator::Equal;
        case Token::Type::NOT_EQUAL_OPER:
            return Operator::NotEqual;
    }
    throwUnexpextedToken();


}

std::unique_ptr<Expression> Parser::readCompOrInsideIf() {
    if(checkTokenType(Token::Type::ROUND_BRACKET_LEFT))
            return readIfExpression();
    else {
        std::unique_ptr<Value> val = readIfValue(getNextToken());
        const auto oper = readCompOperator(getNextToken());
        std::unique_ptr<Value> val2 = readIfValue(getNextToken());
        return std::unique_ptr<CompExpression>(new CompExpression(std::move(val), oper, std::move(val2)));
    }
    throwUnexpextedToken();
}











