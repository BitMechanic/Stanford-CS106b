/**
 * File: pathfinder.cpp
 * --------------------
 * This is the primary file where you'll place most of your code.
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "pathfinder-graph.h"
#include "pathfinder-graphics.h"
#include "pqueue-heap.h"
#include "error.h"
#include "gwindow.h"
#include <map>
#include "pqueue.h"
#include "point.h"
#include "tokenscanner.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "vector.h"
#include "path.h"
#include "lexicon.h"

using namespace std;

/**
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Describes the Pathfinder assignment on the console.  This text has
 * been retained in its original form to preserve the assignment history.
 */
static void giveInstructions();
/**
 * Function: quitAction
 * Usage: quitAction(g);
 * ---------------------
 * Called when the user clicks the Quit button in the control strip.
 */

static Node *findNode(const GPoint &pt, PathfinderGraph *&graph);
static bool responseIsAffirmative(const string& prompt);
static void quitAction();
static void runDijkstra(PathfinderGraph *&graph);
static void kruskalAction(PathfinderGraph *&graph);
static void dijkstraAction();
static void mapAction(PathfinderGraph *&graph);
static void clickAction(const GPoint &pt, PathfinderGraph *&graph);
static void loadMap(PathfinderGraph *graph, string datafile);
static Vector<Set< Node *> > processArcs(Vector<Set< Node *> > MST, Arc *out);


/**
 * Function: main
 * --------------
 * Defines the entry point for the entire application.
 */
int main() {
    GWindow gw(kWindowWidth, kWindowHeight + kControlStripHeight);
    initPathfinderGraphics(gw);
    giveInstructions();
    
    PathfinderGraph *graph = new PathfinderGraph;
    string datafile = "USA";
    loadMap(graph, datafile);
    
    addButton("Map", mapAction, graph);
    addButton("Dijkstra", dijkstraAction);
    addButton("Kruskal", kruskalAction, graph);
    addButton("Quit", quitAction);
    
    defineClickListener(clickAction, graph);
    
    pathfinderEventLoop();
    
    return 0;
}

static void giveInstructions() {
    cout << "This masterful piece of work is a graph extravaganza!" << endl;
    cout << "The main attractions include a lovely visual presentation" << endl;
    cout << "of the graph along with an implementation of Dijkstra's" << endl;
    cout << "shortest path algorithm and Kruskal's computation of" << endl;
    cout << "a minimal spanning tree.  Enjoy!" << endl << endl;
}

        
static void loadMap(PathfinderGraph *graph, string datafile) {
    int result = graph->setMapFile(datafile);
    if (result == -1) {
        cout << "That file doesn't want to load, or doesn't exist." << endl;
        cout << "Make sure you don't use file extensions, just the name of the file." << endl;
        if (responseIsAffirmative("Do you want to try again?")) {
            mapAction(graph);
        }
    }
    
    string map = graph->getMapFile();
    drawPathfinderMap(map);
    Set<Node *> mapnodes = graph->getNodes();
    foreach (Node *next in mapnodes) {
        drawPathfinderNode(next->loc, "Black", next->name);
    }
    Set<Arc *> maparcs = graph->getArcs();
    foreach (Arc *route in maparcs) {
        drawPathfinderArc(route->start->loc, route->finish->loc, "Black");
    }
}

static bool responseIsAffirmative(const string& prompt) {
    while (true) {
        string answer = getLine(prompt);
        if (!answer.empty()) {
            switch (toupper(answer[0])) {
                case 'Y': return true;
                case 'N': return false;
            }
        }
        cout << "Please answer yes or no." << endl;
    }
}

static void clickAction(const GPoint &pt, PathfinderGraph *&graph) {
    Node *found = findNode(pt, graph);
    if (found->name != "VOID") {
        drawPathfinderNode(found->loc, "Red");
        graph->setHighlightedNode(found);
        if (graph->checkNodes()) {
            runDijkstra(graph);
        }
    }
}



static void quitAction() {
    exitGraphics();
}

static void kruskalAction(PathfinderGraph *&graph) {
    
    drawPathfinderMap(graph->getMapFile());// reboot mapfile
    
    Set<Node *> cities = graph->getNodes();
    Vector<Arc *> routes = graph->getKruskalArcs();// get arcs without return trips
    graph->clearArcs();
    
    foreach(Node *edge in cities) {
        edge->arcs.clear();
    }
    
    HeapPQueue<Arc *> *pq = new HeapPQueue<Arc *>;
    
    for (int i = 0; i < routes.size(); i++) {// pull all of the arcs off, enqueue
        pq->enqueue(routes[i], arcCmp);// with arcCmp comparitor from cmfn header
    }
    
    Vector<Set< Node *> > MST;// Vector of sets with one node per set is initial minimal spanning tree
    
    foreach(Node *city in cities) {//populate vector mst
        Set<Node *> zone;
        zone.add(city);
        MST.add(zone);
    }
    
    while (pq->size() != 0) {// whilst there are more arcs in the pqueue, update mst by processing the arcs
        Arc *out = pq->extractMin(arcCmp);
        MST = processArcs(MST, out);
    }
    
    delete pq;
}

static void dijkstraAction() {
    
    cout << "Click on starting and finishing location to cue Dijkstra..." << endl;
    
    
}
            
static Vector<Set< Node *> > processArcs(Vector<Set< Node *> > MST, Arc *out) {
    Vector<Set< Node *> > testMST = MST;// new test mst is only returned if kruskal algorithm is satisfied and adding the arc involves joining 2 sets
    
    Arc *back = new Arc;// create new return trip arc for each arc in the pqueue
    back->start = out->finish;
    back->finish = out->start;
    back->cost = out->cost;
    string distance = realToString(out->cost);
    int One;// initialise ints for positions on the MST vector
    int Two;
    for (int i = 0; i < testMST.size(); i++) {
        if (testMST[i].contains(out->start)) {
            Set< Node *> part1 = testMST[i];// pull set from vector if it contains node from start of arc
            foreach(Node *start in part1) {
                if (start->name == out->start->name) {
                    start->arcs.add(out);// add outgoing arc to ercs
                    One = i;// One int is updated as position in for loop
                }
            }
    }
        if (testMST[i].contains(back->start)) {
            Set< Node *> part2 = testMST[i];// pull set if it contains node from finish
            foreach(Node *finish in part2) {
                if (finish->name == back->start->name) {
                    finish->arcs.add(back);
                    Two = i;// Two int is updated
                }
            }
        }
    }
    Set<Node *> newset = testMST[One];
    if (One != Two) {// If one and two are different, combine and return the new tree
        newset = testMST[One] += testMST[Two];
        testMST[One] = newset;
        testMST.remove(Two);
        cout << distance + ": " + out->start->name + " - " + out->finish->name << endl;
        drawPathfinderNode(out->start->loc, "Red", out->start->name);// Update the console and map etc...
        drawPathfinderNode(out->finish->loc, "Red", out->finish->name);
        drawPathfinderArc(out->start->loc, out->finish->loc, "Red");
        return testMST;
    }
    else {
        cout << distance + ": " + out->start->name + " - " + out->finish->name + "(not needed)" << endl;
        return MST;// Or return the old tree
    }
}

static void mapAction(PathfinderGraph *&graph) {
    cout<< "Please enter the name of the graph data file (without extension): ";
    string mapname = getLine();
    loadMap(graph, mapname);
}

static Node *findNode(const GPoint &pt, PathfinderGraph *&graph) {
    Node *result = new Node;
    result->name = "VOID";
    double x = pt.getX();
    double y = pt.getY();
    Set<Node *> graphnodes = graph->getNodes();
    foreach (Node *next in graphnodes) {
        GPoint nodeloc = next->loc;
        double compx = nodeloc.getX();
        double compy = nodeloc.getY();
        if (x < compx + 8 && x > compx - 8) {
            if (y < compy + 8 && y > compy - 8) {
                result = next;
            }
        }
    }
    return result;
}

static void runDijkstra(PathfinderGraph *&graph) {
    Vector<Node *> selection = graph->getSelected();// Pulls vector of 2 selected nodes
    Node *start = selection[0];
    Node *destination = selection[1];
    string dname = destination->name;
    start->dist = 0;// distance from start is zero
    
    Set<Node *> fixednodes;
    
    HeapPQueue<Path> *paths = new HeapPQueue<Path>;// instantiate path pqueue
    Path startpath;
    startpath.pathcost = 0;// start path distance is zero
    startpath.addNode(start);
    paths->enqueue(startpath, pathCmp);// enqueue with pathCmp comparator (in cmpfn.h header)
    
    Path result;
        while (true) {
        
            Path newpath = paths->extractMin(pathCmp);
            string pathstring = newpath.getRoute();
            cout << "Dequeue the shortest path: " + pathstring << endl;
            Node *next = newpath.getNode();
            string query = next->name;
            if (query == dname) {
                result = newpath;
                break;
            }
            Set<Arc *> startarcs = next->arcs;
           
            fixednodes.add(next);
            double routedist = newpath.pathcost;
            string dist = realToString(routedist);
            cout << "Fix the distance to " + next->name + " at " + dist << endl;
            cout << "Process the arcs out of " + next->name + " (" + newpath.getNextArcs() << endl;
                foreach(Arc *arc in startarcs) {
                    Node *dest = arc->finish;
                    Path nextpath = newpath;
                    if (!fixednodes.contains(dest)) {
                        nextpath.addArc(arc);
                        nextpath.addNode(dest);
                        string pathstring = nextpath.getRoute();
                        cout << "Enqueue the path: " + pathstring << endl;
                        paths->enqueue(nextpath, pathCmp);
                    }
                    else if (fixednodes.contains(dest)) {
                        cout << "   Ignore " + dest->name + " because it's distance is fixed." << endl;
                    }
                    result = newpath;
        }
    }
    delete paths;
    
    Vector<Arc *> resultarcs = result.getArcPath();
    Vector<Node *> resultnodes = result.getNodePath();
    Set<Arc *> maparcs = graph->getArcs();
    Set<Node *> mapnodes = graph->getNodes();
    foreach (Node *next in mapnodes) {
            drawPathfinderNode(next->loc, "Gray", next->name);
    }
    foreach (Arc *route in maparcs) {
            drawPathfinderArc(route->start->loc, route->finish->loc, "Gray");
        
    }
    for (int i = 0; i < resultarcs.size(); i++) {
        Arc *paint = resultarcs[i];
        drawPathfinderArc(paint->start->loc, paint->finish->loc, "Red");
    }
    for (int n = 0; n < resultnodes.size(); n++) {
        Node *draw = resultnodes[n];
        drawPathfinderNode(draw->loc, "Red");
    }

}


