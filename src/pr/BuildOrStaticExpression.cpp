//
// Created by paulina on 06.06.16.
//

#include "BuildOrStaticExpression.h"

std::unordered_map<std::string, int> pr::BuildOrStaticExpression::dependencies;

struct GraphNode {
    GraphNode() : visited(0), alreadyDefined(false) {};
    int index;
    std::string name;
    std::vector<int> graph;
    std::vector<std::string> flags;
    std::vector<std::string> files;
    int visited;
    bool alreadyDefined;
    bool isBuild;
};


std::vector<std::shared_ptr<GraphNode> > nodes;

bool pr::BuildOrStaticExpression::evaluate() {
    std::string res = result->getSingleValue();
    std::vector<std::string> fil;
    if(files != nullptr)
        files->getAllValues(fil);
    auto got = dependencies.find(res);

    std::shared_ptr<GraphNode> resultNode;
    if(got == dependencies.end()) {
        resultNode = std::shared_ptr<GraphNode>(new GraphNode);
        if(function == EndFunction::Build)
            resultNode->isBuild = true;
        else
            resultNode->isBuild = false;
        resultNode->index = nodes.size();
        resultNode->name = res;
        if(flags != nullptr)
            flags->getAllValues(resultNode->flags);
        resultNode->files = fil;
        resultNode->alreadyDefined = true;
        dependencies[res] = nodes.size();
        nodes.push_back(resultNode);
    }
    else {
        resultNode = nodes[got->second];
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
        auto dot = dependencies.find(fil[i]);
        if(dot == dependencies.end()) {
            depNode = std::shared_ptr<GraphNode>(new GraphNode);
            depNode->index = nodes.size();
            depNode->name = fil[i];
            dependencies[fil[i]] = nodes.size();
            nodes.push_back(depNode);
        } else
            depNode = nodes[dot->second];
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

void pr::BuildOrStaticExpression::preparedfs() {
    for (const auto &pair : dependencies) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }
    for(int i = 0; i < nodes.size(); ++i) {
        std::cout<<i << ": ";
        for(int j = 0; j < nodes[i]->graph.size(); ++j) {
            std::cout<< nodes[i]->graph[j] << ", ";
        }
        std::cout<<std::endl;
    }

    std::vector<int> visited;
    visited.resize(dependencies.size());
    std::cout<<"Graph size : "<< visited.size() << std::endl;
    for(int i = 0; i < dependencies.size(); ++i) {
        if(!dfs(i)) {
            std::cout<<nodes[i]->name << "." << std::endl;
            break;
        }
    }
    buildPoprerly();
    return;
}

// 0 - not explored
//1 = being explored
// 2 - fully explored
bool pr::BuildOrStaticExpression::dfs(int index) {
    nodes[index] -> visited = 1;
    for(int i = 0; i < nodes[index]->graph.size(); ++i) {
        int ind2 = nodes[index]->graph[i];
        if(nodes[ind2]->visited == 0) {
            if (!dfs(ind2)) {
                std::cout << nodes[ind2]->name << "->";
                return false;
            }
        }
        else if (nodes[ind2]->visited == 1) {
            std::cout<< nodes[ind2]->name << "->";
            return false;
        }
    }
    nodes[index] -> visited = 2;
    return true;
}

void pr::BuildOrStaticExpression::buildPoprerly() {
    for(int i = 0; i < dependencies.size(); ++i) {
        if(!nodes[i] -> visited != 4)
            dfs2(i);
    }
}

bool pr::BuildOrStaticExpression::dfs2(int index) {
    if(nodes[index]->visited == 4)
        return true;
    nodes[index]->visited = 4;
    for(int i = 0; i < nodes[index]->graph.size(); ++i) {
        int ind2 = nodes[index]->graph[i];
        if(nodes[ind2]->alreadyDefined == true)
            dfs2(ind2);
    }
    if(nodes[index]->alreadyDefined == false)
        return true;
    std::cout<<(nodes[index]->isBuild ? "build " : "staticlib ");
    std::cout<<nodes[index]->name;
    std::cout<<" files : ";
    for(int i = 0; i < nodes[index]->files.size(); ++i)
        std::cout<<nodes[index]->files[i]<<" ";
    std::cout<<" flags : ";
    for(int i = 0; i < nodes[index]->flags.size(); ++i)
        std::cout<<nodes[index]->flags[i]<<" ";
    std::cout<<std::endl;
}












