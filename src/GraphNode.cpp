//
// Created by paulina on 12.06.16.
//

#include "GraphNode.h"

std::unordered_map<std::string, int> Resolver::dependencies;
std::vector<std::shared_ptr<GraphNode> > Resolver::nodes;



std::string pr::BuildOrStaticExpression::preparedfs() {
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
    std::string s;
    for(int i = 0; i < dependencies.size(); ++i) {
        if(!dfs(i, s)) {
            s += nodes[i]->name  + ".";
            throw std::runtime_error("Cycle detected: " + s);
        }
    }

    return buildPoprerly();
}

// 0 - not explored
//1 = being explored
// 2 - fully explored
bool pr::BuildOrStaticExpression::dfs(int index, std::string & s) {
    nodes[index] -> visited = 1;
    for(int i = 0; i < nodes[index]->graph.size(); ++i) {
        int ind2 = nodes[index]->graph[i];
        if(nodes[ind2]->visited == 0) {
            if (!dfs(ind2, s)) {
                s += nodes[ind2]->name + "->";
                return false;
            }
        }
        else if (nodes[ind2]->visited == 1) {
            s+= nodes[ind2]->name + "->";
            return false;
        }
    }
    nodes[index] -> visited = 2;
    return true;
}

std::string pr::BuildOrStaticExpression::buildPoprerly() {
    std::string s;
    for(int i = 0; i < dependencies.size(); ++i) {
        if(!nodes[i] -> visited != 4)
            dfs2(i, s);
    }
    return s;
}

bool pr::BuildOrStaticExpression::dfs2(int index, std::string & s) {
    if(nodes[index]->visited == 4)
        return true;
    nodes[index]->visited = 4;
    for(int i = 0; i < nodes[index]->graph.size(); ++i) {
        int ind2 = nodes[index]->graph[i];
        if(nodes[ind2]->alreadyDefined == true)
            dfs2(ind2, s);
    }
    if(nodes[index]->alreadyDefined == false)
        return true;
    switch(nodes[index]->isBuild) {
        case true:
            s+="g++ ";
            for(int i = 0; i < nodes[index]->files.size(); ++i)
                s+=nodes[index]->files[i] + " ";
            s+="-o " + nodes[index]->name + " ";

            for(int i = 0; i < nodes[index]->flags.size(); ++i)
                s+= nodes[index]->flags[i] + " ";
            break;
        case false:
            s+= "ar rcs " + nodes[index]->name + " ";
            for(int i = 0; i < nodes[index]->files.size(); ++i)
                s+= nodes[index]->files[i] + " ";
            for(int i = 0; i < nodes[index]->flags.size(); ++i)
                s+= nodes[index]->flags[i] + " ";
            break;
    }
    s += "\n";
    /*std::cout<<(nodes[index]->isBuild ? "g++ " : "ar rcs ");
    for(int i = 0; i < nodes[index]->files.size(); ++i)
        std::cout<<nodes[index]->files[i]<<" ";
    std::cout<<"-o pmaketemp/"<<nodes[index]->name<<" ";

    for(int i = 0; i < nodes[index]->flags.size(); ++i)
        std::cout<<nodes[index]->flags[i]<<" ";
    std::cout<<std::endl;*/
}