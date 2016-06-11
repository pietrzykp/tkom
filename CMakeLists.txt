cmake_minimum_required(VERSION 3.5)
project(tkom2)
set(CXX_STANDARD 1y)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(SOURCE_FILES main.cpp CppScanner.cpp CppScanner.h Token.cpp Token.h Parser.cpp Parser.h pr/Expression.cpp pr/Expression.h pr/OrExpression.cpp pr/OrExpression.h pr/AndExpression.cpp pr/AndExpression.h pr/CompExpression.cpp pr/CompExpression.h pr/Operator.cpp pr/Operator.h pr/Value.cpp pr/Value.h pr/VariableDeclaration.cpp pr/VariableDeclaration.h pr/Expressions.cpp pr/Expressions.h pr/IfExpression.cpp pr/IfExpression.h pr/FunctionCall.cpp pr/FunctionCall.h pr/FunctionDeclaration.cpp pr/FunctionDeclaration.h pr/ForExpression.cpp pr/ForExpression.h pr/BuildOrStaticExpression.cpp pr/BuildOrStaticExpression.h pr/VariableStack.cpp pr/VariableStack.h pr/FunctionStack.cpp pr/FunctionStack.h)
add_executable(tkom2 ${SOURCE_FILES})

add_definitions(-std=c++1y)