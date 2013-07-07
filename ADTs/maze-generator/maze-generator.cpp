/**
 * File: maze-generator.cpp
 * ------------------------
 * Presents an adaptation of Kruskal's algorithm to generate mazes.
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "simpio.h"
#include "set.h"
#include "vector.h"
#include "maze-types.h"
#include "maze-graphics.h"
#include "foreach.h"
#include "random.h"
#include "strlib.h"



static void buildCells(Vector<Set<cell> >& cells, int dimension);
static void createWalls(MazeGeneratorView& display, Vector<wall>& mazeWalls, int dimension);
int readInteger(int minDimension, int maxDimension);
static void shuffleWalls(Vector<wall>& mazeWalls);
bool checkChambers(int x1, int y1, int x2, int y2, Vector<Set<cell> >& cells);
static void removeWalls(MazeGeneratorView& display, Vector<wall>& mazeWalls, Vector<Set<cell> >& cells, int dimension);

	
int main()  {
    int dimension;
    Vector<Set<cell> > cells;
    Vector<wall> mazeWalls;
    MazeGeneratorView display;
	while (true) {
		dimension = readInteger(7, 50);
		if (dimension == 0) break;
		display.setDimension(dimension);
        display.drawBorder();
        buildCells(cells, dimension);
        createWalls(display, mazeWalls, dimension);
        shuffleWalls(mazeWalls);
        removeWalls(display, mazeWalls, cells, dimension);
	}

	return 0;
}


int readInteger(int minDimension, int maxDimension) {
    while (true) {
        cout << "What should the dimension of your maze be(0 to exit)? ";
		int response = getInteger();
		if (response == 0) return response;
        if (response >= minDimension && response <= maxDimension) return response;
		cout << "Please enter a number between "
        << minDimension << " and "
        << maxDimension << ", inclusive." << endl;
	}
}

static void shuffleWalls(Vector<wall>& mazeWalls) {
    int random1, random2;
    for (int i = 0; i < mazeWalls.size(); i++) {// shuffles the walls in the vector so they come off in random order
        random1 = randomInteger(0, mazeWalls.size() - 1);
        random2 = randomInteger(0, mazeWalls.size() - 1);
        wall temp = mazeWalls[random1];
        mazeWalls[random1] = mazeWalls[random2];
        mazeWalls[random2] = temp;
    }
    
}

static void buildCells(Vector<Set<cell> >& cells, int dimension) {
    for (int x = 0; x < dimension; x++) {// builds a vector of cells within sets. Each set is a chamber
        for (int y = 0; y < dimension; y++) {
            cell newcell;
            newcell.col = x;
            newcell.row = y;
            Set<cell> newchamber;
            newchamber.add(newcell);
            cells.add(newchamber);
        }
    }
}

static void createWalls(MazeGeneratorView& display, Vector<wall>& mazeWalls, int dimension) {
    wall horizontal, vertical;
    for (int x = 0; x < dimension; x++) {// creates the walls with the appropriate values for x and y of adjacent cells
        for (int y = 0; y < dimension; y++) {
            if (x < dimension - 1) {
                horizontal.one.col = x;
                horizontal.one.row = y;
                horizontal.two.col = x + 1;
                horizontal.two.row = y;
                mazeWalls.add(horizontal);
                display.drawWall(horizontal);
            }
            if (y < dimension - 1) {
                vertical.one.col = x;
                vertical.one.row = y;
                vertical.two.col = x;
                vertical.two.row = y + 1;
                mazeWalls.add(vertical);
                display.drawWall(vertical);
            }
        }
    }
}

static void removeWalls(MazeGeneratorView& display, Vector<wall>& mazeWalls, Vector<Set<cell> >& cells, int dimension) {
    int count = 0;
    int check = dimension * dimension;
    while (count < check && mazeWalls.size() > 0) {
            wall nextwall = mazeWalls.get(0);
            int x1 = nextwall.one.col;
            int y1 = nextwall.one.row;
            int x2 = nextwall.two.col;
            int y2 = nextwall.two.row;
            mazeWalls.remove(0);// removes wall from vector after checking, regardless of whether its being removed from the maze
            if (checkChambers(x1, y1, x2, y2, cells) == true) {
                display.removeWall(nextwall);// removes wall from maze if its separated by two chambers
                pause(50);
                count++;
                if (count == check) {
                    break;
            }
        }
    }
}

bool checkChambers(int x1, int y1, int x2, int y2, Vector<Set<cell> >& cells) {
    Set<cell> testsetone;
    Set<cell> testsettwo;
    int vectorindex1;
    int vectorindex2;
    for (int index = 0; index < cells.size(); index++) {
        Set<cell> chamber = cells.get(index);
            foreach (cell testcell in chamber) { // checks to find adjacent cells and loads them into values of                     testsetone, testsettwo and also finds index
                int x = testcell.col;
                int y = testcell.row;
                if (x == x1 && y == y1) {
                    testsetone = chamber;
                    vectorindex1 = index;
                }
                if (x == x2 && y == y2) {
                    testsettwo = chamber;
                    vectorindex2 = index;
            }
        }
    }
        

        if (testsetone == testsettwo) {
            return false;
        }
        else if (testsetone != testsettwo) {
            testsetone += testsettwo;// merges sets if chambers are seperate, then deletes one and adds the other to the vector
            cells.remove(vectorindex1);
            cells.insert(vectorindex1, testsetone);
            cells.remove(vectorindex2);
            return true;
        }
    return false;
    }
   