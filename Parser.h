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
#include "pr/BuildOrStaticExpression.h"

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

    std::unique_ptr<Expression> readVariableDeclaration();
    std::unique_ptr<Expression> readFunctionDeclaration();
    std::unique_ptr<Expression> readFunctionCall();
    std::unique_ptr<Expression> readForExpression();
    std::unique_ptr<Expression> readBuildExpression();
    std::unique_ptr<Expression> readStaticExpression();
    std::unique_ptr<Expression> readBuildOrStaticExpression(EndFunction f);

    std::unique_ptr<Expressions> getBracketExpressions();

    void readFunctionHelper(std::vector<std::string> & paramsNames);
    void readForHelper(std::vector<std::string> & paramNames, std::vector<std::shared_ptr<Value> > & lists);
    void readCallHelper(std::vector<std::shared_ptr<Value> > &  values);

    bool unparsable = false;
    int index = 0;

    Token getNextToken();
    Token getToken();
    Token requireToken(Token::Type expectedType);

    void throwUnexpextedToken(Token::Type expected);

    std::shared_ptr<pr::Value> readNonArray(Token token);
    std::shared_ptr<pr::Value> readNonRecursiveValue(Token token);
    std::shared_ptr<pr::Value> readRecursiveValue();

    Operator readCompOperator(Token token);

    bool checkTokenType(Token::Type type) const;
public:
    Parser(std::unique_ptr<CppScanner> scanner);
    ~Parser() {};
    std::unique_ptr<Expression> parse();

};


#endif //TKOM2_PARSER_H
