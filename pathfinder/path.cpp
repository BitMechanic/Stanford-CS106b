/**
 * File: path.cpp
 * --------------
 * This file implements the Path class.
 */

#include "path.h"
#include "strlib.h"

void Path::addArc(Arc *newone) {
        pathcost += newone->cost;
        pathofarcs.add(newone);
}

void Path::addNode(Node *newnode) {
        newnode->dist = pathcost;
        pathofnodes.add(newnode);
}

Node *Path::getNode() {
    Node *result = pathofnodes[pathofnodes.size() -1];
    return result;
}

std::string Path::getRoute() {
    string result = "";
    for (int i = 0; i < pathofnodes.size(); i++) {
        Node *next = pathofnodes[i];
        string nodename = next->name;
        if (i < pathofnodes.size() - 1) {
            result = result + " " + nodename + " ->";
        }
        else if (i == pathofnodes.size() - 1) {
            string coststring = integerToString(pathcost);
            result = result + " " + nodename + " (" + coststring + ")";
        }
    }
    return result;
}

std::string Path::getNextArcs() {
    string result = "";
    Node *last = pathofnodes[pathofnodes.size() -1];
    Set<Arc *> nextarcs = last->arcs;
    foreach(Arc* next in nextarcs) {
        Node *place = next->finish;
        string add = place->name;
        result = result + add + ", ";
    }
    result[result.size() - 1] = ')';
    return result;
}

Vector<Node *> Path::getNodePath() {
    return pathofnodes;
}
Vector<Arc *> Path::getArcPath() {
    return pathofarcs;
}