//
// Created by paulina on 12.06.16.
//

#ifndef TKOM2_GRAPHNODE_H
#define TKOM2_GRAPHNODE_H


#include <vector>
#include <string>
#include "pr/BuildOrStaticExpression.h"

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

class Resolver {
public:
    static std::unordered_map<std::string, int> dependencies;
    static std::vector<std::shared_ptr<GraphNode> > nodes;
    static std::string resolve();
};

#endif //TKOM2_GRAPHNODE_H
