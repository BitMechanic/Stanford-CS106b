/**
 * File: dominosa.cpp
 * ------------------
 * This animates the brute-force discovery of a solution
 * to a 2 x n dominosa board.
 */

#include <iostream>
#include <cmath>
using namespace std;

#include "simpio.h"
#include "grid.h"
#include "random.h"
#include "set.h"
#include "map.h"
#include "dominosa-graphics.h"

static void welcome();
static int getIntegerInRange(string prompt, int low, int high);
static void populateBoard(Grid<int>& board, int low, int high);
static bool canSolveBoard(DominosaDisplay& display, Grid<int>& board, Map<coord, int>& numbers, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int numColumns);
static void certifyPairings(DominosaDisplay& display, Grid<int>& board, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int numColumns);
static bool findPairs(DominosaDisplay& display, Grid<int>& board, Map<coord, int>& numbers, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int numColumns, int col);
static void tryPairing(DominosaDisplay& display, Grid<int>& board, Map<coord, int>& numbers, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int i, int col);
static void deletePairings(DominosaDisplay& display, Grid<int>& board, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int col);
static void buildNumbers( Grid<int>& board, Map<coord, int>& numbers, int numColumns);

int main() {
	DominosaDisplay display;
	welcome();
	while (true) {
		int numColumns = getIntegerInRange("How many columns? [0 to exit]: ", 9, 25);
		if (numColumns == 0) break;
		Grid<int> board(2, numColumns);
        Set<Set< int> > verticalpairings;// create two sets to check pairings, horizontal and vertical- so can choose correct way to erase on rewind
        Set<Set< int> > horizontalpairings;
		populateBoard(board, 1, ceil(2 * sqrt(numColumns)));
        Map<coord, int> numbers;
        buildNumbers(board, numbers, numColumns);
		display.drawBoard(board);
		if (canSolveBoard(display, board, numbers, verticalpairings, horizontalpairings, numColumns)) {
			cout << "The board can be solved, and one such solution is drawn above." << endl;
		} else {
			cout << "This board you see can't be solved." << endl;
		}
	}
	
	cout << "Okay, thanks for watching, and come back soon." << endl;
    cout << "Click the mouse anywhere in the window to exit." << endl;
	return 0;
}

static void welcome() {
	cout << "Here we'll illustrate the use of recursive backtracking to" << endl;
	cout << "discover a solution to various 2 x n Dominosa boards.  In some" << endl;
	cout << "cases there won't be any solutions, and in the cases where there are" << endl;
	cout << "multiple solutions, we'll just find one of them." << endl;
	cout << endl;
}

static int getIntegerInRange(string prompt, int low, int high) {
	while (true) {
		int response = getInteger(prompt);
		if (response == 0 || (response >= low && response <= high)) return response;
		cout << "Sorry, but I can't use that number." << endl;
	}
}

static void populateBoard(Grid<int>& board, int low, int high) {
	for (int row = 0; row < board.numRows(); row++) {
		for (int col = 0; col < board.numCols(); col++) {
			board[row][col] = randomInteger(low, high);
		}
	}
}

static bool canSolveBoard(DominosaDisplay& display, Grid<int>& board, Map<coord, int>& numbers, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int numColumns) {
    int col = 0;
    if (findPairs(display, board, numbers, verticalpairings, horizontalpairings, numColumns, col)) {
        certifyPairings(display, board, verticalpairings, horizontalpairings, numColumns);
        return true;
    }
      
    
    else {
        
	return false;
    }
}

static void certifyPairings(DominosaDisplay& display, Grid<int>& board, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int col) {
    //for however long the grid is, certify the pairings
    //update the display
    cout << "We've reached certifyPairings" << endl;
}

static void buildNumbers( Grid<int>& board, Map<coord, int>& numbers, int numColumns) {
    for (int row = 0; row < 2; row++) {
        for (int column = 0; column < numColumns; column++) {
            int number = board[row][column];
            coord location;
            location.row = row;
            location.col = column;
            numbers.put(location, number);
        }
    }
}

static bool findPairs(DominosaDisplay& display, Grid<int>& board, Map<coord, int>& numbers, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int numColumns, int col) {
    int numcolumn = verticalpairings.size() + horizontalpairings.size();
    if (numcolumn == numColumns) return true; // base case, if the set of sets has reached the size of numColumns, it's done
    
   
    for (int i = 1; i < 3; i++) { // i for the choice between 1 vertical pair, or 2 pairs of horizontal pairings
       
        tryPairing(display, board, numbers, verticalpairings, horizontalpairings, i, numcolumn);
        //provisionally pair- new column vertical or horizontal
        numcolumn = verticalpairings.size() + horizontalpairings.size();
        
        if (findPairs(display, board, numbers, verticalpairings, horizontalpairings, numColumns, numcolumn)) return true;
        //if (findPairs) return true (recur until stop)
        
    }
    numcolumn = verticalpairings.size() + horizontalpairings.size();
    deletePairings(display, board, verticalpairings, horizontalpairings, numcolumn);
    // go back and start again from an alternate choice at an earlier stage
	return false;

    
}

static void tryPairing(DominosaDisplay& display, Grid<int>& board, Map<coord, int>& numbers, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int i, int col) {

    if (i == 1) {
        coord coordone, coordtwo;
        coordone.row = 0;
        coordone.col = col;
        coordtwo.row = 1;
        coordtwo.col = col;
        int one = numbers.get(coordone);
        int two = numbers.get(coordtwo);
        Set<int> pair;
        if (horizontalpairings.contains(pair) == false && verticalpairings.contains(pair) == false) {
            verticalpairings.add(pair);
            display.provisonallyPair(coordone, coordtwo);
        }
        else if (verticalpairings.contains(pair) == true || horizontalpairings.contains(pair) == true) {
            display.vetoProvisionalPairing(coordone, coordtwo);
            display.eraseProvisionalPairing(coordone, coordtwo);
        }
    }
            
    else if (i == 2) {
        coord coordone, coordtwo, coordthree, coordfour;
        coordone.row = 0;
        coordone.col = col;
        coordtwo.row = 0;
        coordtwo.col = col + 1;
        coordthree.row = 1;
        coordthree.col = col;
        coordfour.row = 1;
        coordfour.col = col + 1;
        int oneupper = numbers.get(coordone);
        int twoupper = numbers.get(coordtwo);
        int onelower = numbers.get(coordthree);
        int twolower = numbers.get(coordfour);
        Vector<int> pairone;
        Vector<int> pairtwo;
        if (oneupper < twoupper) {
            pairone.add(oneupper);
            pairone.add(twoupper);
        }
        else if (oneupper > twoupper) {
            pairone.add(twoupper);
            pairone.add(oneupper);
        }
        if (onelower < twolower) {
            pairtwo.add(onelower);
            pairtwo.add(twolower);
        }
        else if (onelower > twolower) {
            pairtwo.add(twolower);
            pairtwo.add(onelower);
        }
        if (horizontalpairings.contains(pairone) == false && horizontalpairings.contains(pairtwo) == false && verticalpairings.contains(pairone) == false && verticalpairings.contains(pairtwo) == false) {
            verticalpairings.add(pairone);
            verticalpairings.add(pairtwo);
            display.provisonallyPair(coordone, coordtwo);
            display.provisonallyPair(coordthree, coordfour);
        }
        else if (verticalpairings.contains(pairone) == false && horizontalpairings.contains(pairone) == false) { if (verticalpairings.contains(pairtwo) == true|| horizontalpairings.contains(pairtwo) == true) {
            display.provisonallyPair(coordone, coordtwo);
            display.vetoProvisionalPairing(coordthree, coordfour);
            display.eraseProvisionalPairing(coordone, coordtwo);
            display.eraseProvisionalPairing(coordthree, coordfour);
            }
        }
        else if (verticalpairings.contains(pairtwo) == false && horizontalpairings.contains(pairtwo) == false) { if (verticalpairings.contains(pairone) == true|| horizontalpairings.contains(pairone) == true)  {
            display.vetoProvisionalPairing(coordone, coordtwo);
            display.provisonallyPair(coordthree, coordfour);
            display.eraseProvisionalPairing(coordone, coordtwo);
            display.eraseProvisionalPairing(coordthree, coordfour);
        }
        else {
            display.vetoProvisionalPairing(coordone, coordtwo);
            display.vetoProvisionalPairing(coordthree, coordfour);
            display.eraseProvisionalPairing(coordone, coordtwo);
            display.eraseProvisionalPairing(coordthree, coordfour);
            }
        }
    }
}

static void deletePairings(DominosaDisplay& display, Grid<int>& board, Set<Set< int> > verticalpairings, Set<Set< int> > horizontalpairings, int col) {
    
}

