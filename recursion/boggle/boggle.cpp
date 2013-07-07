/**
 * File: boggle.cpp
 * ----------------
 * Implements the game of Boggle.
 */
 
#include <cctype>
#include <iostream>
using namespace std;

#include "simpio.h"
#include "gwindow.h"
#include "gboggle.h"
#include "map.h"
#include "grid.h"
#include "random.h"
#include "lexicon.h"

const int kBoggleWindowWidth = 650;
const int kBoggleWindowHeight = 350;
const int kBoggleBoardSize = 4;
const int kBoggleCubesSize = 16;


const string kStandardCubes[16] = {
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const string kBigBoggleCubes[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};


static void playGame();
static void welcome();
static void giveInstructions();
static bool responseIsAffirmative(const string& prompt);
static void createBoard(Vector<Vector<string> >& cubes, Grid<char>& board);
static void forceBoardConfig(Grid<char>& board);
static bool isWord(string playerword, Lexicon& english);
static bool notUsed(string playerword, Set<string>& usedwords);
static bool longEnough(string playerword);
static bool findStart(string playerword, Grid<char>& board);
static bool findSquares(string playerword, Grid<char>& board, Vector<GPoint>& path, Set<GPoint>& usedsquares, Vector<int>& lastwordsize, string& found);
static void nextSquare(string playerword, Grid<char>& board, Vector<GPoint>& path, Set<GPoint>& usedsquares, string& found, int dir);
static void removeSquare(Vector<GPoint>& path, Set<GPoint>& usedsquares, Vector<int>& lastwordsize, string& found);
static void highlightWord(Vector<GPoint>& path);
static bool wordHasGrown(Vector<int>& lastwordsize, string& found);
static void computerTurn(Grid<char>& board, Set<string>& usedwords, Lexicon& english);
static bool findWords(Grid<char>& board, Vector<GPoint>& path, Vector<int>& lastwordsize, Set<GPoint>& usedsquares, Set<string>& foundwords, string& compfound, Set<string>& usedwords, Lexicon& english, bool endcheck);
static void buildWord(Grid<char>& board, Vector<GPoint>& path, Set<GPoint>& usedsquares, Set<string>& foundwords, string& compfound, Set<string>& usedwords, Lexicon& english, int dir);
static void processSquare(Vector<GPoint>& path, Set<GPoint>& usedsquares, Set<string>& foundwords, string& compfound, Set<string>& usedwords, Lexicon& english, string& temporary, GPoint& result);
    


int main() {
    
    while (true) {
        
        playGame();
        
        if (!responseIsAffirmative("Would you like to play again?")) {
            break;
        }
    }

   return 0;
}

static void playGame() {
    
    GWindow gw(kBoggleWindowWidth, kBoggleWindowHeight);
    initGBoggle(gw);
    welcome();
    Lexicon english("EnglishWords.dat");
    if (responseIsAffirmative("Do you need instructions? ")) {
        giveInstructions();
    }
    
    Vector<Vector<string> > cubes;
    Grid<char> board(kBoggleBoardSize, kBoggleBoardSize);
    drawBoard(kBoggleBoardSize, kBoggleBoardSize);
    createBoard(cubes, board);
    Set<string> usedwords;
    cout << "I'll give you a chance to set up the board to your specification, which makes it easier to confirm your boggle program is working." << endl;
    if (responseIsAffirmative("Do you want to force the board configuration? ")) {
        forceBoardConfig(board);
    }
    else {
        createBoard(cubes, board);
    }
    for (int boardx = 0; boardx < kBoggleBoardSize; boardx++) {
        for (int boardy = 0; boardy < kBoggleBoardSize   ; boardy++) {
            char letter = board.get(boardx, boardy);
            labelCube(boardx, boardy,letter);
        }
    }
    cout << endl;
    cout << "Ok, take all the time you want and find all the words you can!  Signal that you're finished by entering an empty line." << endl;
    while (true) {
        cout << "Enter a word :";
        string playerwordinit = getLine();
        string playerword = toUpperCase(playerwordinit);
        if (playerword == "") {
            break;
        }
        if (isWord(playerword, english) && notUsed(playerword, usedwords) && longEnough(playerword)) {
            if (findStart(playerword, board)) {
                usedwords.add(playerword);
            }
            else {
                cout << "You can't make that word." << endl;
            }
        }
    }
    computerTurn(board, usedwords, english);

}

static void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

static void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
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

static void createBoard(Vector<Vector<string> >& cubes, Grid<char>& board) {
    for (int i = 0; i < 16; i++) {
        Vector<string> onecube;
        for (int letter = 0; letter < 6; letter++) {
            string cube = kStandardCubes[i];
            string side = cube.substr(letter, 1);
            onecube.add(side);
        }
        cubes.add(onecube);
    }
    for (int swap = 0; swap < cubes.size(); swap++) {
        int swap2 = randomInteger(swap, cubes.size() - 1);
        Vector<string> element1 = cubes.get(swap);
        Vector<string> element2 = cubes.get(swap2);
        cubes.set(swap2, element1);
        cubes.set(swap, element2);
    }
    Vector<string> selections;
    for (int x = 0; x < 16; x++) {
        Vector<string> cubethrow = cubes.get(x);
        int random = randomInteger(0, 5);
        string selection = cubethrow.get(random);
        selections.add(selection);
    }
    int selectionsindex = 0;
    for (int boardx = 0; boardx < kBoggleBoardSize; boardx++) {
        for (int boardy = 0; boardy < kBoggleBoardSize   ; boardy++) {
            string position = selections.get(selectionsindex);
            char position2 = position[0];
            board.set(boardx, boardy, position2);
            selectionsindex++;
        }
    }
}

static void forceBoardConfig(Grid<char>& board) {
    cout << "Enter a 16-character string to identify which letters you want on the cubes." << endl;
    cout << "The first 4 letters are the cubes on the top row from left to right, the next 4 letters are the second row, and so on." << endl;
    cout << "Enter the string: ";
    string playerselect = getLine();
    cout << "This is the playerselect " + playerselect << endl;
    if (playerselect.size() < kBoggleCubesSize) {
        cout << "That string isnt long enough!" << endl;
        forceBoardConfig(board);
    }
    else if (playerselect.size() >= kBoggleCubesSize) {
        int stringindex = 0;
        for (int boardx = 0; boardx < kBoggleBoardSize; boardx++) {
            for (int boardy = 0; boardy < kBoggleBoardSize   ; boardy++) {
                char select = playerselect[stringindex];
                char upperselect = toupper(select);
                board.set(boardx, boardy, upperselect);
                stringindex++;
            }
        }
    }
}

static bool isWord(string playerword, Lexicon& english) {
    if (english.contains(playerword)) {
    return true;
    }
    else {
        cout << "That isn't a word!" << endl;
    }
    return false;
}

static bool notUsed(string playerword, Set<string>& usedwords) {
    if (usedwords.contains(playerword)) {
        cout << "You already used that word." << endl;
        return false;
    }
    return true;
}

static bool longEnough(string playerword) {
    if (playerword.size() < 4) {
        cout << "I'm sorry, but we have our standards." << endl;
        cout << "That word doesn't meet the minimum word length." << endl;
        return false;
    }
    return true;
}

static bool findStart(string playerword, Grid<char>& board) {
    char beginning = playerword[0];
    char uppercase = toupper(beginning);
    for (int x = 0; x < kBoggleBoardSize; x++) {
        for (int y = 0; y < kBoggleBoardSize; y++) {// loop cycles through each space of the board looking for start letter
            char boardlocation = board.get(x, y);
            if (uppercase == boardlocation) {
                Vector<GPoint> path;// stores path of matched letters
                Vector<int> lastwordsize;// stores size of the word in the previous turn to check wordhasgrown
                Set<GPoint> usedsquares;// stores the usedsquares so they arent re-used in same word
                string found = playerword.substr(0, 1);
                lastwordsize.insert(0, 1);
                GPoint start(x, y);
                path.add(start);
                usedsquares.add(start);
                if (findSquares(playerword, board, path, usedsquares, lastwordsize, found)) {
                    highlightWord(path);
                    recordWordForPlayer(playerword, HUMAN);
                    return true;
                }
            }
        }
    }
    return false;
}

static bool findSquares(string playerword, Grid<char>& board, Vector<GPoint>& path, Set<GPoint>& usedsquares, Vector<int>& lastwordsize, string& found) {
    
    if (playerword == found) {// Base case of found word matches the player input word
        return true;
    }
    
    if (found.size() == 0) {// if the found word goes back to empty, return false and cycle to the next start letter
        return false;
    }
    
        for (int dir = 0; dir < 8; dir++) {// loop of 8, one per possible direction
            
            nextSquare(playerword, board, path, usedsquares, found, dir);// returns GPoint of next square
        
               if (wordHasGrown(lastwordsize, found)) {// if the word has grown
                    if (findSquares(playerword, board, path, usedsquares, lastwordsize, found)) {// recurse to new loop till its solved
                        return true; 
                }
            }
        }
    removeSquare(path, usedsquares, lastwordsize, found);// remove square after the loop and rewind to earlier decision
    return false;
}

        
static void nextSquare(string playerword, Grid<char>& board, Vector<GPoint>& path, Set<GPoint>& usedsquares, string& found, int dir) {
    
    GPoint newstart = path.get(path.size() - 1);
    int x = newstart.getX();
    int y = newstart.getY();
    int length = found.size();
    char target = playerword[length];
    if (dir == 0) {// dir is loop number from findsquares- direction
        if (board.inBounds(x + 1, y)) {
            char thisone = board[x + 1][y]; // for each cycle of the loop check a letter on the board around the source tile
            GPoint result(x + 1, y);
                if (target == thisone && !usedsquares.contains(result)) {
                    found = found + target;
                    path.add(result);
                    usedsquares.add(result);
            }
        }
    }
    if (dir == 1) {
        if (board.inBounds(x - 1, y)) {
            char thisone = board[x - 1][y];
            GPoint result(x - 1, y);
                if (target == thisone && !usedsquares.contains(result)) {
                    found = found + target;
                    path.add(result);
                    usedsquares.add(result);
            }
        }
    }
    if (dir == 2) {
        if (board.inBounds(x, y + 1)) {
            char thisone = board[x][y + 1];
            GPoint result(x, y + 1);
                if (target == thisone && !usedsquares.contains(result)) {
                    found = found + target;
                    path.add(result);
                    usedsquares.add(result);
            }
        }
    }
    if (dir == 3) {
        if (board.inBounds(x, y - 1)) {
            char thisone = board[x][y - 1];
            GPoint result(x, y - 1);
                if (target == thisone && !usedsquares.contains(result)) {
                    found = found + target;
                    path.add(result);
                    usedsquares.add(result);
            }
        }
    }
    if (dir == 4) {
        if (board.inBounds(x - 1, y - 1)) {
            char thisone = board[x - 1][y - 1];
            GPoint result(x - 1, y - 1);
                if (target == thisone && !usedsquares.contains(result)) {
                    found = found + target;
                    path.add(result);
                    usedsquares.add(result);
            }
        }
    }
    if (dir == 5) {
        if (board.inBounds(x + 1, y - 1)) {
            char thisone = board[x + 1][y - 1];
            GPoint result(x + 1, y - 1);
                if (target == thisone && !usedsquares.contains(result)) {
                    found = found + target;
                    path.add(result);
                    usedsquares.add(result);
            }
        }
    }
    if (dir == 6) {
        if (board.inBounds(x + 1, y + 1)) {
            char thisone = board[x + 1][y + 1];
            GPoint result(x + 1, y + 1);
                if (target == thisone && !usedsquares.contains(result)) {
                    found = found + target;
                    path.add(result);
                    usedsquares.add(result);
            }
        }
    }
    if (dir == 7) {
        if (board.inBounds(x - 1, y + 1)) {
            char thisone = board[x - 1][y + 1];
            GPoint result(x - 1, y + 1);
                if (target == thisone && !usedsquares.contains(result)) {
                    found = found + target;
                    path.add(result);
                    usedsquares.add(result);
            }
        }
    }
}
    
static void removeSquare(Vector<GPoint>& path, Set<GPoint>& usedsquares, Vector<int>& lastwordsize, string& found) {
    if (found.length() > 0) {
    GPoint erase = path.get(path.size() - 1);
    found.erase(found.length() - 1);
    int newwordsize = found.length();
    lastwordsize.set(0, newwordsize);
    path.remove(path.size() - 1);
    usedsquares.remove(erase);
    }
}

static void highlightWord(Vector<GPoint>& path) {
    for (int i = 0; i < path.size(); i++) {
        GPoint update1 = path.get(i);
        int x = update1.getX();
        int y = update1.getY();
        highlightCube(x, y, true);
    }
    pause(200);
    for (int n = 0; n < path.size(); n++) {
        GPoint update2 = path.get(n);
        int x = update2.getX();
        int y = update2.getY();
        highlightCube(x, y, false);
    }
}


static bool wordHasGrown(Vector<int>& lastwordsize, string& found) {//
    int currentsize = found.length();
    int lastsize = lastwordsize.get(0);
    if (lastsize >= currentsize) {
        lastwordsize.set(0, currentsize);
        return false;
    }
    
    else if (lastsize < currentsize){
        lastwordsize.set(0, currentsize);
        return true;
    }
}

static void computerTurn(Grid<char>& board, Set<string>& usedwords, Lexicon& english) {
    Set<string> foundwords;
    for (int x = 0; x <= kBoggleBoardSize; x++) {
        for (int y = 0; y <= kBoggleBoardSize; y++) {
            string compfound;
                if (x < kBoggleBoardSize && y < kBoggleBoardSize) {
                    char boardlocation = board.get(x, y);
                    compfound = compfound + boardlocation;
            }
            
            Vector<GPoint> path;// stores path of matched letters
            Vector<int> lastwordsize;// stores size of the word in the previous turn to check wordhasgrown
            Set<GPoint> usedsquares;// stores the usedsquares so they arent re-used in same word
            bool endcheck = false;// during the loop send out false for recursive base case
            if (x == kBoggleBoardSize || y == kBoggleBoardSize) {
                endcheck = true;// hits the final extra loop and sends true
            }
            
            lastwordsize.insert(0, 1);
            GPoint start(x, y);
            path.add(start);
            usedsquares.add(start);
            if (findWords(board, path, lastwordsize, usedsquares, foundwords, compfound, usedwords, english, endcheck)) {
                break;
            }
        }
    }
    
    foreach (string word in foundwords) {
        recordWordForPlayer(word, COMPUTER);
    }
    
}

static bool findWords(Grid<char>& board, Vector<GPoint>& path, Vector<int>& lastwordsize, Set<GPoint>& usedsquares, Set<string>& foundwords, string& compfound, Set<string>& usedwords, Lexicon& english, bool endcheck) {
    if (endcheck == true) {// base case is the extra loop in computerturn that sends out endcheck bool
        return true;
    }
    
    if (compfound.size() == 0) {
        return false;
    }
    
        for (int dir = 0; dir < 8; dir++) {
            
            buildWord(board, path, usedsquares, foundwords, compfound, usedwords, english, dir);
            
            if (wordHasGrown(lastwordsize, compfound)) {// re-use wordhasgrown function
                if (findWords(board, path, lastwordsize, usedsquares, foundwords, compfound, usedwords, english, endcheck)) {
                    return true;
            }
        }
    }
    removeSquare(path, usedsquares, lastwordsize, compfound);// re-use removesquare function
    return false;
}
        
static void buildWord(Grid<char>& board, Vector<GPoint>& path, Set<GPoint>& usedsquares, Set<string>& foundwords, string& compfound, Set<string>& usedwords, Lexicon& english, int dir) {
    
    GPoint newstart = path.get(path.size() - 1);
    int x = newstart.getX();
    int y = newstart.getY();
    string temporary = compfound;
    
    if (dir == 0) {// dir is loop number from findsquares- direction
        if (board.inBounds(x + 1, y)) {
            char thisone = board[x + 1][y]; // for each cycle of the loop check a letter on the board around the source tile
            temporary = temporary + thisone;
            GPoint result(x + 1, y);
            if (usedsquares.contains(result) == false) {
            processSquare(path, usedsquares, foundwords, compfound, usedwords, english, temporary, result);
            }
        }
    }
        
    if (dir == 1) {
        if (board.inBounds(x - 1, y)) {
            char thisone = board[x - 1][y];
            temporary = temporary + thisone;
            GPoint result(x - 1, y);
            if (usedsquares.contains(result) == false) {
            processSquare(path, usedsquares, foundwords, compfound, usedwords, english, temporary, result);
            }
        }
    }
        
    if (dir == 2) {
        if (board.inBounds(x, y + 1)) {
            char thisone = board[x][y + 1];
            temporary = temporary + thisone;
            GPoint result(x, y + 1);
            if (usedsquares.contains(result) == false) {
            processSquare(path, usedsquares, foundwords, compfound, usedwords, english, temporary, result);
            }
        }
    }
        
    if (dir == 3) {
        if (board.inBounds(x, y - 1)) {
            char thisone = board[x][y - 1];
            temporary = temporary + thisone;
            GPoint result(x, y - 1);
            if (usedsquares.contains(result) == false) {
            processSquare(path, usedsquares, foundwords, compfound, usedwords, english, temporary, result);
            }
        }
    }
        
    if (dir == 4) {
        if (board.inBounds(x - 1, y - 1)) {
            char thisone = board[x - 1][y - 1];
            temporary = temporary + thisone;
            GPoint result(x - 1, y - 1);
            if (usedsquares.contains(result) == false) {
            processSquare(path, usedsquares, foundwords, compfound, usedwords, english, temporary, result);
            }
        }
    }
        
    if (dir == 5) {
        if (board.inBounds(x + 1, y - 1)) {
            char thisone = board[x + 1][y - 1];
            temporary = temporary + thisone;
            GPoint result(x + 1, y - 1);
            if (usedsquares.contains(result) == false) {
            processSquare(path, usedsquares, foundwords, compfound, usedwords, english, temporary, result);
            }
        }
    }
        
    if (dir == 6) {
        if (board.inBounds(x + 1, y + 1)) {
            char thisone = board[x + 1][y + 1];
            temporary = temporary + thisone;
            GPoint result(x + 1, y + 1);
            if (usedsquares.contains(result) == false) {
            processSquare(path, usedsquares, foundwords, compfound, usedwords, english, temporary, result);
            }
        }
    }
        
    if (dir == 7) {
        if (board.inBounds(x - 1, y + 1)) {
            char thisone = board[x - 1][y + 1];
            temporary = temporary + thisone;
            GPoint result(x - 1, y + 1);
            if (usedsquares.contains(result) == false) {
            processSquare(path, usedsquares, foundwords, compfound, usedwords, english, temporary, result);
            }
        }
    }
}

static void processSquare(Vector<GPoint>& path, Set<GPoint>& usedsquares, Set<string>& foundwords, string& compfound, Set<string>& usedwords, Lexicon& english, string& temporary, GPoint& result) {
    
    if (english.containsPrefix(temporary) || english.contains(temporary)) {
            path.add(result);
            usedsquares.add(result);
            compfound = temporary;
            if (english.contains(compfound) && compfound.size() >= 4 && !usedwords.contains(compfound)) {
                foundwords.add(compfound);
        }
    }
}
