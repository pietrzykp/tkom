//
// Created by paulina on 03.06.16.
//

#ifndef TKOM2_PARSER_H
#define TKOM2_PARSER_H

#include <memory>
#include <vector>
#include "CppScanner.h"
#include "pr/Expression.h"
#include "pr/Value.h"
#include "pr/Operator.h"
#include "pr/IfExpression.h"

using namespace pr;

class Parser {
    std::unique_ptr<CppScanner> scanner;
    std::vector<Token> readTokens;

    std::unique_ptr<Expression> readExpressions();
    std::unique_ptr<Expression> readExpression();

    std::unique_ptr<IfExpression> readIfExpression();
    std::unique_ptr<Expression> readOrExpression(std::unique_ptr<Expression> exp);
    std::unique_ptr<Expression> readAndExpression(std::unique_ptr<Expression> exp);
    std::unique_ptr<Expression> readCompOrInsideIf();

    std::unique_ptr<Expression> readVariableDelaration();
    std::unique_ptr<Expression> readFunctionCall();
    std::unique_ptr<Expressions> getBracketExpressions();

    bool unparsable = false;
    int index = 0;

    Token getNextToken();
    Token getToken();
    Token requireToken(Token::Type expectedType);

    void throwUnexpextedToken() { exit(0); };

    std::unique_ptr<pr::Value> readIfValue(Token token);
    std::unique_ptr<pr::Value> readRecursiveValue();

    Operator readCompOperator(Token token);

    bool checkTokenType(Token::Type type) const;
public:
    Parser(std::unique_ptr<CppScanner> scanner);
    ~Parser() {};
    std::unique_ptr<Expression> parse();

};


#endif //TKOM2_PARSER_H
