/*
 * File: path.h
 * ------------
 * This file is the interface for a Path class, which consists of a
 * sequence of arcs.
 */

#ifndef _path_h
#define _path_h

#include "vector.h"
#include "set.h"
#include "graphtypes.h"


class Path {

public:
    
    void addNode(Node *newnode);
	void addArc(Arc *newone);
	int pathcost;
    Node *getNode();
    std::string getRoute();
    std::string getNextArcs();
    Vector<Node *> getNodePath();
    Vector<Arc *> getArcPath();
    
private:
    Vector<Node *> pathofnodes;
    Vector<Arc *> pathofarcs;
    
};



#endif
