//
// Created by paulina on 12.06.16.
//

#include "GraphNode.h"

std::unordered_map<std::string, int> Resolver::dependencies;
std::vector<std::shared_ptr<GraphNode> > Resolver::nodes;



std::string Resolver::resolve() {
    std::string s;
    for(int i = 0; i < dependencies.size(); ++i) {
        if(!checkCycles(i, s)) {
            s += nodes[i]->name  + ".";
            throw std::runtime_error("Cycle detected: " + s);
        }
    }

    return buildExecutionString();
}

bool Resolver::checkCycles(int index, std::string &s) {
    nodes[index] -> visited = 1;
    for(int i = 0; i < nodes[index]->graph.size(); ++i) {
        int ind2 = nodes[index]->graph[i];
        if(nodes[ind2]->visited == 0) {
            if (!checkCycles(ind2, s)) {
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

std::string Resolver::buildExecutionString() {
    std::string s;
    for(int i = 0; i < dependencies.size(); ++i) {
        if(!nodes[i] -> visited != 4)
            getRightOrder(i, s);
    }
    return s;
}

bool Resolver::getRightOrder(int index, std::string &s) {
    if(nodes[index]->visited == 4)
        return true;
    nodes[index]->visited = 4;
    for(int i = 0; i < nodes[index]->graph.size(); ++i) {
        int ind2 = nodes[index]->graph[i];
        if(nodes[ind2]->alreadyDefined == true)
            getRightOrder(ind2, s);
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
}