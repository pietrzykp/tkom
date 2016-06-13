//
// Created by paulina on 06.06.16.
//

#include "BuildOrStaticExpression.h"
#include "../GraphNode.h"


bool pr::BuildOrStaticExpression::evaluate() {
    std::string res = result->getSingleValue();
    std::vector<std::string> fil;
    if(files != nullptr)
        files->getAllValues(fil);
    auto got = Resolver::dependencies.find(res);

    std::shared_ptr<GraphNode> resultNode;
    if(got == Resolver::dependencies.end()) {
        resultNode = std::shared_ptr<GraphNode>(new GraphNode);
        if(function == EndFunction::Build)
            resultNode->isBuild = true;
        else
            resultNode->isBuild = false;
        resultNode->index = Resolver::nodes.size();
        resultNode->name = res;
        if(flags != nullptr)
            flags->getAllValues(resultNode->flags);
        resultNode->files = fil;
        resultNode->alreadyDefined = true;
        Resolver::dependencies[res] = Resolver::nodes.size();
        Resolver::nodes.push_back(resultNode);
    }
    else {
        resultNode = Resolver::nodes[got->second];
        if(function == EndFunction::Build)
            resultNode->isBuild = true;
        else
            resultNode->isBuild = false;
        if(resultNode->alreadyDefined)
            ; // throw error
        else resultNode->alreadyDefined = true;
        if(flags != nullptr)
            flags->getAllValues(resultNode->flags);
        resultNode->files = fil;
    }

    for(int i = 0; i < fil.size() ; ++i) {

        std::shared_ptr<GraphNode> depNode;
        auto dot = Resolver::dependencies.find(fil[i]);
        if(dot == Resolver::dependencies.end()) {
            depNode = std::shared_ptr<GraphNode>(new GraphNode);
            depNode->index = Resolver::nodes.size();
            depNode->name = fil[i];
            Resolver::dependencies[fil[i]] = Resolver::nodes.size();
            Resolver::nodes.push_back(depNode);
        } else
            depNode = Resolver::nodes[dot->second];
        resultNode->graph.push_back(depNode->index);
    }
}

std::string pr::BuildOrStaticExpression::toString() const {
    std::string s;
    std::string b = (function == EndFunction::Build ? "build" : "staticlib");
    s += b + " (" + result->toString() + ", " + files->toString() + ", "
         + (flags == nullptr ? " null " : flags ->toString()) + ") endbuild";
    return s;
}













