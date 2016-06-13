//
// Created by paulina on 12.06.16.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "TokenTests"
#include <boost/test/included/unit_test.hpp>
#include "../src/Token.h"
#include "../src/CppScanner.h"
#include "../src/Parser.h"
#include "../src/GraphNode.h"

BOOST_AUTO_TEST_CASE(default_token_is_error) {
    Token t;
    BOOST_CHECK_EQUAL(t.getType(), Token::Type::ERROR);
}

BOOST_AUTO_TEST_CASE(token_var) {
    std::istringstream i("var for in if else def call build staticlib = && || == != ; , [ ] ( ) { } jou 'jou'");
    BOOST_TEST_MESSAGE("aaa");
    CppScanner c(i);
    int index = 0;
    while(1) {
        c.readNextToken();
        Token t = c.getToken();
        if(c.getToken().getType() == Token::Type::EOF_IDENT)
            break;
        BOOST_CHECK_EQUAL(t.getType(), index++);
    }
}

BOOST_AUTO_TEST_CASE(all_file) {
    std::istringstream ii("#komentarz \n"
     "var temp = ['aaa'];\n"
     "build(hello, ['main.o']);\n"
     "staticlib();\n"
     "def buildWithFlags(outNames) {"
        "if(temp == 'aaa') {\n"
            "for(o in onames) {\n"
                "build(o);#komentarz\n"
            "}\n"
        "} else {\n"
        "}\n"
     "}\n");
    std::vector<Token::Type> types = { Token::Type::VAR, Token::Type::IDENTIFIER, Token::Type::ASSIGN_OPER, Token::Type::SQUARE_BRACKET_LEFT ,Token::Type::STRING, Token::Type::SQUARE_BRACKET_RIGHT ,Token::Type::SEMICOLON,
                                       Token::Type::BUILD, Token::Type::ROUND_BRACKET_LEFT, Token::Type::IDENTIFIER, Token::Type::COMMA, Token::Type::SQUARE_BRACKET_LEFT, Token::Type::STRING, Token::Type::SQUARE_BRACKET_RIGHT, Token::Type::ROUND_BRACKET_RIGHT, Token::Type::SEMICOLON,
                                       Token::Type::STATICLIB, Token::Type::ROUND_BRACKET_LEFT, Token::Type::ROUND_BRACKET_RIGHT, Token::Type::SEMICOLON,
                                       Token::Type::DEF, Token::Type::IDENTIFIER, Token::Type::ROUND_BRACKET_LEFT, Token::Type::IDENTIFIER, Token::Type::ROUND_BRACKET_RIGHT, Token::Type::CURLY_BRACKET_LEFT,
                                       Token::Type::IF, Token::Type::ROUND_BRACKET_LEFT, Token::Type::IDENTIFIER, Token::Type::EQUAL_OPER, Token::Type::STRING, Token::Type::ROUND_BRACKET_RIGHT, Token::Type::CURLY_BRACKET_LEFT,
                                       Token::Type::FOR, Token::Type::ROUND_BRACKET_LEFT, Token::Type::IDENTIFIER, Token::Type::IN, Token::Type::IDENTIFIER, Token::Type::ROUND_BRACKET_RIGHT, Token::Type::CURLY_BRACKET_LEFT,
                                       Token::Type::BUILD, Token::Type::ROUND_BRACKET_LEFT, Token::Type::IDENTIFIER, Token::Type::ROUND_BRACKET_RIGHT, Token::Type::SEMICOLON,
                                       Token::Type::CURLY_BRACKET_RIGHT,
                                       Token::Type::CURLY_BRACKET_RIGHT, Token::Type::ELSE, Token::Type::CURLY_BRACKET_LEFT,
                                        Token::Type::CURLY_BRACKET_RIGHT,
                                       Token::Type::CURLY_BRACKET_RIGHT, Token::Type::EOF_IDENT

    };
    CppScanner c(ii);
    for (int i = 0; i < types.size(); ++i) {
        c.readNextToken();
        BOOST_CHECK_EQUAL(c.getToken().getType(), types[i]);
    }
}

BOOST_AUTO_TEST_CASE(var_expr) {
    std::istringstream i("var temp = ['aaa', 'bbb'];");
    Parser p(std::shared_ptr<CppScanner>(new CppScanner(i)));
    std::shared_ptr<Expression> e = p.parse();
    BOOST_CHECK_EQUAL(e->toString(), "expr: decl temp:  [- aaa, bbb,  -] \n"
    " endexpr\n");
}

BOOST_AUTO_TEST_CASE(def_if_build_call) {
    std::istringstream i("def buildWithFlags(outNames, inNames) { if(temp == 'aaa' || 'aaa' == 'aaa' && 'i' != i) { build(a,b); } } call buildWithFlags('aaa', 'bbb');");
    Parser p(std::shared_ptr<CppScanner>(new CppScanner(i)));
    std::shared_ptr<Expression> e = p.parse();
    BOOST_CHECK_EQUAL(e->toString(), "expr: fundef buildWithFlags params: outNames inNames  funins expr: if ( ( ( valtemp cmp aaa ) &&  ) || ( ( aaa cmp aaa ) && ( i cmp vali ) ) ) -> expr: build (vala, valb,  null ) endbuild endexpr\n"
            " else null\n"
            " endexpr\n"
            " endfundef \n"
            " endexpr\n"
            "expr: call buildWithFlags params : aaa, bbb, endcall\n"
            " endexpr\n"
            "");
}

BOOST_AUTO_TEST_CASE(check_if_cycle_detected) {
    std::istringstream i("build('aaa', ['bbb', 'ccc']);\n"
                               "build('bbb', ['ddd', 'eee']);\n"
                               "build('ddd', ['aaa', 'uuu']);");
    Parser p(std::shared_ptr<CppScanner>(new CppScanner(i)));
    try {
        std::shared_ptr<Expression> e = p.parse();
        e->evaluate();
        Resolver::resolve();
    } catch(std::runtime_error err) {
        BOOST_CHECK_EQUAL(err.what(), "Cycle detected: aaa->ddd->bbb->aaa.");
        Resolver::dependencies.clear();
        Resolver::nodes.clear();
        return;
    }
    BOOST_CHECK_EQUAL(1,2);
    Resolver::dependencies.clear();
    Resolver::nodes.clear();
}

BOOST_AUTO_TEST_CASE(whole_build_example) {
    std::istringstream i("\nvar moduleFlags = '-Wall';\n"
                                 "\n"
                                 "var headerLibFiles = ['header.o', 'aaaaaa.txt', 'factoraal.o']; #komentarz2\n"
                                 "build('aaa', ['bbb', 'ccc']);\n"
                                 "build('bbb', ['ddd', 'eee']);\n"
                                 "build('ddd', ['ggg', 'uuu']);\n"
                                 "\n"
                                 "staticlib('header.a', headerLibFiles, moduleFlags);");
    Parser p(std::shared_ptr<CppScanner>(new CppScanner(i)));
    try {
        std::shared_ptr<Expression> e = p.parse();
        e->evaluate();
        std::string result = Resolver::resolve();
        int x= 1;
        BOOST_CHECK_EQUAL(result, "g++ ggg uuu -o ddd \n"
                "g++ ddd eee -o bbb \n"
                "g++ bbb ccc -o aaa \n"
                "ar rcs header.a header.o aaaaaa.txt factoraal.o -Wall \n");
    } catch(std::runtime_error err) {
        BOOST_CHECK_EQUAL(1, 2);
    }
    Resolver::dependencies.clear();
    Resolver::nodes.clear();
}
