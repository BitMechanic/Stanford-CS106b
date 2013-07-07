/**
 * File: life.cpp
 * --------------
 * Implements the Game of Life.
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "console.h" // required of all files that contain the main function
#include "simpio.h"  // for getLine
#include "strlib.h"
#include "random.h"
#include "vector.h"
#include "grid.h"
#include "life-constants.h"  // for kMaxAge
#include "life-graphics.h"   // for class LifeDisplay
#include "gevents.h"


static void welcome();
static void setUp(LifeDisplay& display, Grid<int>& thisgeneration);
int setSpeed();
int speedConverter(string number);
static void cellFlagger(Grid<int>& nextgeneration, Grid<int>& birthsanddeaths);
static void lifeGenerator(Grid<int>& nextgeneration, Grid<int>& birthsanddeaths);
static void updateDisplay(Grid<int>& thisgeneration, LifeDisplay& display);
void runSimulation(Grid<int>& thisgeneration, LifeDisplay& display, int speed);


int main() {
    LifeDisplay display;
    display.setTitle("Game of Life");
    display.setDimensions(40, 60);
    Grid<int> thisgeneration(40, 60);
    welcome();
    setUp(display, thisgeneration);
    int speed = setSpeed();
    runSimulation(thisgeneration, display, speed);
    
    return 0;
}

void runSimulation(Grid<int>& thisgeneration, LifeDisplay& display, int speed) {
    int nrows = thisgeneration.numRows();
    int ncols = thisgeneration.numCols();
    while (true) {
        if (speed == 4) {
            cout << ("Hit [enter] to continue...");
            cin.ignore();
        }
        else if (speed == 3) {
            pause(1000);
        }
        else if (speed == 2) {
            pause(250);
        }
        else if (speed == 1) {
            pause(0);
        }
        Grid<int> birthsanddeaths(nrows, ncols);
        Grid<int> nextgeneration(nrows, ncols);
        nextgeneration = thisgeneration;
        cellFlagger(nextgeneration, birthsanddeaths);
        lifeGenerator(nextgeneration, birthsanddeaths);
        thisgeneration = nextgeneration;
        updateDisplay(thisgeneration, display);
        }
    }

static void welcome() {
	cout << "Welcome to the game of Life, a simulation of the lifecycle of a bacteria colony." << endl;
	cout << "Cells live and die by the following rules:" << endl << endl;
	cout << "\tA cell with 1 or fewer neighbors dies of loneliness" << endl;
	cout << "\tLocations with 2 neighbors remain stable" << endl;
	cout << "\tLocations with 3 neighbors will spontaneously create life" << endl;
	cout << "\tLocations with 4 or more neighbors die of overcrowding" << endl << endl;
	cout << "In the animation, new cells are dark and fade to gray as they age." << endl << endl;
    cout << ("Hit [enter] to continue....   ");
    cin.ignore();
}

static void setUp(LifeDisplay& display, Grid<int>& thisgeneration) {
    cout << "You can start your colony with random cells or read from a prepared file." << endl;
    cout << ("Enter name of colony file (or RETURN to seed randomly): ");
    string setupmessage = getLine();
    if (setupmessage == "") {
        int nrows = randomInteger(40, 60);
        int ncols = randomInteger(40, 60);
        thisgeneration.resize(nrows, ncols);
        display.setTitle("Random Colony"); //sets up window and grid for random game
        display.setDimensions(nrows, ncols);
        for (int x = 0; x < nrows; x++) {
            for (int y = 0; y < ncols; y++) {
                bool life = randomChance(0.5);
                if (life == true) {
                    int cell = randomInteger(1, kMaxAge);
                    thisgeneration.set(x, y, cell);
                    display.drawCellAt(x, y, cell);
                }
                else if (life == false) {
                    thisgeneration.set(x, y, 0);
                }
            }
        }
    }
    else if (setupmessage != "") { 
        ifstream inp;
        inp.open(setupmessage.c_str());
        if (inp.is_open() == true) {
            if (inp.fail()) { error("Could not open file");
                cout << "Try again..." << endl;
                inp.clear();
                setUp(display, thisgeneration);
            }
            string row;
            int linecount = 0;
            int size = 0;
            Vector<string> filereadout;
            while (getline(inp, row)) {
                char dash = row.find("-");
                if (dash == string::npos) {
                    inp.ignore();
                }
                else if (dash != string::npos) {
                    filereadout.push_back(row);
                    size = row.size();
                    linecount++;
                }
                
            }
            int nrows = linecount;
            int ncols = size;
            thisgeneration.resize(nrows, ncols);
            display.setTitle(setupmessage.c_str()); //sets up window and grid for game from file
            display.setDimensions(nrows, ncols);
            for (int x = 0; x < nrows; x++) {
                string lines = filereadout.get(x);
                for (int y = 0; y < lines.size(); y++) {
                    char cells = lines[y];
                    if (cells == 'X') {
                        thisgeneration.set(x, y, 5);
                        display.drawCellAt(x, y, 5);
                    }
                    else if (cells != 'X') {
                        thisgeneration.set(x, y, 0);
                    }
                }
            }
        }

        
        else if (inp.is_open() == false) {
            cout << "That file isn't in the directory, please try again." << endl;
            setUp(display, thisgeneration);
        }
        else {
            cout << "Fuck a duck... whats happening?" << endl;
            setUp(display, thisgeneration);
        }
        
    }
}


int setSpeed() {
    cout << "You choose how fast to run the simulation." << endl;
    cout << "\t1 = As fast as this chip can go!" << endl;
    cout << "\t2 = Not too fast, this is a school zone." << endl;
    cout << "\t3 = Nice and slow so I can watch everything that happens." << endl;
    cout << "\t4 = Require enter key be pressed before advancing to next generation." << endl;
    int speed = speedConverter("your choice: ");
    return speed;
}

int speedConverter(string number) {
    cout << number;
    int speed = getInteger();
    if (speed < 1 || speed > 4) {
        cout << "That isn't a valid integer, try again." << endl;
        setSpeed();
    }
    return speed;
}

static void cellFlagger(Grid<int>& nextgeneration, Grid<int>& birthsanddeaths) {
    int count;
    int nrows = nextgeneration.numRows();
    int ncols = nextgeneration.numCols();
    for (int x = 0; x < nrows; x++) {
        for (int y = 0; y < ncols; y++) {// counts through the cells around the cell
                count = 0;
                if (nextgeneration.inBounds(x + 1, y) == true) {
                    int check = nextgeneration[x + 1][y];
                    if (check >= 1) {
                        count++;
                    }
                }
                if (nextgeneration.inBounds(x - 1, y) == true) {
                    int check = nextgeneration[x - 1][y];
                    if (check >= 1) {
                        count++;
                    }
                }
                if (nextgeneration.inBounds(x, y + 1) == true) {
                    int check = nextgeneration[x][y + 1];
                    if (check >= 1) {
                        count++;
                    }
                }
                if (nextgeneration.inBounds(x, y - 1) == true) {
                    int check = nextgeneration[x][y - 1];
                    if (check >= 1) {
                        count++;
                    }
                }
                if (nextgeneration.inBounds(x - 1, y - 1) == true) {
                    int check = nextgeneration[x - 1][y - 1];
                    if (check >= 1) {
                        count++;
                    }
                }
                if (nextgeneration.inBounds(x + 1, y - 1) == true) {
                    int check = nextgeneration[x + 1][y - 1];
                    if (check >= 1) {
                        count++;
                    }
                }
                if (nextgeneration.inBounds(x + 1, y + 1) == true) {
                    int check = nextgeneration[x + 1][y + 1];
                    if (check >= 1) {
                        count++;
                    }
                }
                if (nextgeneration.inBounds(x - 1, y + 1) == true) {
                    int check = nextgeneration[x - 1][y + 1];
                    if (check >= 1) {
                        count++;
                    }
                }
            if (count != 2 && count != 3) {// marks cells for death
                birthsanddeaths.set(x, y, -3);
            }
            if (count == 3) {// marks squares for new cells
                birthsanddeaths.set(x, y, 3);
                }
          }
    }
}

static void lifeGenerator(Grid<int>& nextgeneration, Grid<int>& birthsanddeaths) {
    int nrows = nextgeneration.numRows();
    int ncols = nextgeneration.numCols();
    for (int turn = 1; turn < 4; turn++) {
        for (int x = 0; x < nrows; x++) {
            for (int y = 0; y < ncols; y++) {
                if (turn == 1) {// deletes the cells that are marked by cellflagger to die
                    int dead = birthsanddeaths.get(x, y);
                    if (dead == -3) {
                        nextgeneration.set(x, y, 0);
                    }
                }
                else if (turn == 2) {// processes the age of the ones that remain
                    int live = nextgeneration.get(x, y);
                    if (live > 0 && live < kMaxAge) {
                        live++;
                        nextgeneration.set(x, y, live);
                    }
                }
                else if (turn == 3) {// creates new cells on squares marked by cellflagger
                    int born = birthsanddeaths.get(x, y);
                    if (born == 3) { if (nextgeneration[x][y] == 0) {
                        nextgeneration.set(x, y, 1);
                        }
                    }
                }
            }
        }
    }
}

static void updateDisplay(Grid<int>& thisgeneration, LifeDisplay& display) {
    int nrows = thisgeneration.numRows();
    int ncols = thisgeneration.numCols();
        display.setDimensions(nrows, ncols);
        for (int x = 0; x < nrows; x++) {
            for (int y = 0; y < ncols; y++) {
                if (thisgeneration[x][y] > 0) {
                    int cell = thisgeneration[x][y];
                    display.drawCellAt(x, y, cell);
            }
        }

    }
}

