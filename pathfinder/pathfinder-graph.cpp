/**
 * File: pathfinder-graph.cpp
 * --------------------------
 * Provides the (fairly obvious) implementation of
 * the PathfinderGraph class.
 */

#include "pathfinder-graph.h"
#include "tokenscanner.h"
#include "strlib.h"
#include "simpio.h"

using namespace std;

int PathfinderGraph::setMapFile(const string& filename) {
    mapFile = "images/" + filename + ".jpg";
    highlightedNode = NULL;
    int result = loadDataFile(filename);
    return result;
}

const string& PathfinderGraph::getMapFile() const {
    return mapFile;
}

void PathfinderGraph::setHighlightedNode(Node *node) {
    if (selected.size() >= 2) {
        selected.clear();
    }
    selected.add(node);
    highlightedNode = node;
}

Node *PathfinderGraph::getHighlightedNode() const {
    return highlightedNode;
}

bool PathfinderGraph::checkNodes() {
    if (selected.size() == 2) {
        return true;
    }
    return false;
}


int PathfinderGraph::loadDataFile(const string& filename) {
    dataFile.nodeMap.clear();
    dataFile.nodes.clear();
    dataFile.arcs.clear();
    kruskalarcs.clear();
    

    map<string, Node *>::iterator iter;
    ifstream inp;
    string datafile = "data-files/" + filename + ".txt";
    inp.open(datafile.c_str());
        if (inp.is_open() == true) {
            if (inp.fail()) { error("Could not open file");
                inp.clear();
                return -1;
            }
    }
    string row;
    Vector<string> filereadout;
    while (getline(inp, row)) {
        filereadout.add(row);
    }
    inp.close();

    filereadout.remove(0);
    filereadout.remove(0);
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    
    while (true) {
        string line = filereadout[0];
        if (line == "ARCS") break;
        Node *newnode = new Node;
        double x;
        double y;
        scanner.setInput(line);
        string nodename;
            for (int i = 0; i < 3; i++) {
                string next = scanner.nextToken();
                if (i == 0) {
                    
                    newnode->name = next;
                    nodename = next;
                    newnode->dist = INFIN_VAL;
                }
                else if (i == 1) {
                    
                    x = stringToReal(next);
                }
                else if (i == 2) {
                    
                    y = stringToReal(next);
                }
            }
        GPoint location(x, y);
        newnode->loc = location;
        dataFile.nodeMap.insert(pair<string, Node *> (nodename, newnode));

        filereadout.remove(0);
    }
    
    filereadout.remove(0);
    
    while (filereadout.size() > 0) {
        string line = filereadout[0];
        scanner.setInput(line);
        Arc *newarc1 = new Arc;
        Arc *newarc2 = new Arc;
        Node *currnode = new Node;
        Node *nextnode = new Node;
        string one;
        string two;
        for (int i = 0; i < 3; i++) {
            if (i == 0) {
                one = scanner.nextToken();
                iter = dataFile.nodeMap.find(one);
                currnode = iter->second;
                newarc1->start = currnode;
                newarc2->finish = currnode;
            }
            else if (i == 1) {
                two = scanner.nextToken();
                iter = dataFile.nodeMap.find(two);
                nextnode = iter->second;
                newarc1->finish = nextnode;
                newarc2->start = nextnode;
            }
            else if (i == 2) {
                scanner.scanNumbers();
                string thirdstring = scanner.nextToken();
                double third = stringToReal(thirdstring);
                newarc1->cost = third;
                newarc2->cost = third;
            }
        }
        kruskalarcs.add(newarc1);
        currnode->arcs.add(newarc1);
        nextnode->arcs.add(newarc2);
        dataFile.arcs.add(newarc1);
        dataFile.arcs.add(newarc2);
        filereadout.remove(0);
    }
    
    foreach (string word in dataFile.nodeMap) {
        iter = dataFile.nodeMap.find(word);
        Node *nextnode = iter->second;
        dataFile.nodes.add(nextnode);
    }
    if (filereadout.isEmpty()) return 1;
    return 0;
}

Set<Node *> PathfinderGraph::getNodes() {
    Set<Node *> result = dataFile.nodes;
    return result;
}

Set<Arc *> PathfinderGraph::getArcs() {
    Set<Arc *> result = dataFile.arcs;
    return result;
}

Vector<Node *> PathfinderGraph::getSelected() {
    return selected;
}

void PathfinderGraph::clearArcs() {
    dataFile.arcs.clear();
    foreach(Node *next in dataFile.nodes) {
        next->arcs.clear();
    }
}

Vector<Arc *> PathfinderGraph::getKruskalArcs() {
    return kruskalarcs;
}
