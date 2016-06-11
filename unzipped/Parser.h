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
    std::shared_ptr<CppScanner> scanner;
    std::vector<Token> readTokens;

    std::shared_ptr<Expression> readExpressions();
    std::shared_ptr<Expression> readExpression();

    std::shared_ptr<IfExpression> readIfExpression();
    std::shared_ptr<Expression> readOrExpression(std::shared_ptr<Expression> exp);
    std::shared_ptr<Expression> readAndExpression(std::shared_ptr<Expression> exp);
    std::shared_ptr<Expression> readCompOrInsideIf();

    std::shared_ptr<Expression> readVariableDeclaration();
    std::shared_ptr<Expression> readFunctionDeclaration();
    std::shared_ptr<Expression> readFunctionCall();
    std::shared_ptr<Expression> readForExpression();
    std::shared_ptr<Expression> readBuildExpression();
    std::shared_ptr<Expression> readStaticExpression();
    std::shared_ptr<Expression> readBuildOrStaticExpression(EndFunction f);

    std::shared_ptr<Expressions> getBracketExpressions();

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
    Parser(std::shared_ptr<CppScanner> scanner);
    ~Parser() {};
    std::shared_ptr<Expression> parse();

};


#endif //TKOM2_PARSER_H
