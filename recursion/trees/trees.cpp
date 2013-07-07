/**
 * File: trees.cpp
 * ---------------
 * Draws a recursive tree as specified in the Assignment 3 handout.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
using namespace std;

#include "console.h" // required of all CS106 C++ programs
#include "gwindow.h" // for GWindow class and its setTitle, setColor, and drawPolarLine methods
#include "gtypes.h"  // for GPoint class
#include "random.h"  // for randomChance function

const static double kWindowWidth = 600;
const static double kWindowHeight = 600;
const static string kWindowTitle = "Recursive Trees";
const static double kTrunkLength  = kWindowHeight/4;
const static double kShrinkFactor = 0.70;
const static int kBranchAngleSeparation = 15;
const static int kTrunkStartAngle = 90;
const static string kLeafColor = "#2e8b57";
const static string kTrunkColor = "#8b7765";
const static double kBranchProbability = 1.0;

void drawTree(GWindow& window, int turn, int order, GPoint trunkbase, double length, int angle);
void growTree(GWindow& window, int turn, GPoint trunkbase, double length, int angle);

const static int kHighestOrder = 5;
int main() {
    GWindow window(kWindowWidth, kWindowHeight);
    window.setWindowTitle(kWindowTitle);
    cout << "Repeatedly click the mouse in the graphics window to draw " << endl;
    cout << "recursive trees of higher and higher order." << endl;
    GPoint trunkbase(window.getWidth()/2, window.getHeight());
    for (int turn = 0; turn <= kHighestOrder; turn++) {
        waitForClick();
        window.clear();
        growTree(window, turn, trunkbase, kTrunkLength, kTrunkStartAngle);
    }
    
    cout << endl;
    cout << "All trees through order " << kHighestOrder << " have been drawn." << endl;
    cout << "Click the mouse anywhere in the graphics window to quit." << endl;
    waitForClick();
    return 0;
}

void growTree(GWindow& window, int turn, GPoint trunkbase, double length, int angle){
    
    drawTree(window, turn, 0, trunkbase, length, angle);
}

void drawTree(GWindow& window, int turn, int order, GPoint trunkbase, double length, int angle) {
    int grow = turn + 1;
    
    if (order >= grow) {
       
        return;
    }
    
        window.setColor(order > 2 ? kLeafColor : kTrunkColor);
        if (randomChance(kBranchProbability) == true) {
        GPoint base = window.drawPolarLine(trunkbase, length, angle);
    
        
        drawTree(window, turn, order + 1, base, length * kShrinkFactor, angle - 45);
        drawTree(window, turn, order + 1, base, length * kShrinkFactor, angle - 30);
        drawTree(window, turn, order + 1, base, length * kShrinkFactor, angle - 15);
        drawTree(window, turn, order + 1, base, length * kShrinkFactor, angle);
        drawTree(window, turn, order + 1, base, length * kShrinkFactor, angle + 15);
        drawTree(window, turn, order + 1, base, length * kShrinkFactor, angle + 30);
        drawTree(window, turn, order + 1, base, length * kShrinkFactor, angle + 45);
        
    
        return drawTree(window, turn, order + 1, base, length * kShrinkFactor, angle);
        }
    }
    // update this function to wrap around another version of drawTree, which
    // recursively draws the tree of the specified order....

