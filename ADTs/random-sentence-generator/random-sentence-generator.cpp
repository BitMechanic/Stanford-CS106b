/**
 * File: random-sentence-generator.cpp
 * -----------------------------------
 * Presents a short program capable of reading in
 * context-free grammar files and generating arbitrary
 * sentences from them.
 */

#include <iostream>
#include <fstream>
using namespace std;

#include "console.h"
#include "simpio.h"   // for getLine
#include "strlib.h"   // for toLowerCase, trim
#include "gevents.h"
#include "queue.h"
#include "map.h"
#include <string>
#include "random.h"
#include "tokenscanner.h"

static const string kGrammarsDirectory = "grammars/";
static const string kGrammarFileExtension = ".g";
static string getNormalizedFilename(string filename);
static bool isValidGrammarFilename(string filename);
static string getFileName();
static void readInGrammar(string filename, Map<string, Vector<string> >& grammar);
static void generateSentence(Map<string, Vector<string> >& grammar, string& randomsentence);


int main() {
    while (true) {
        string filename = getFileName();
        if (filename.empty()) break;
        Map<string, Vector<string> > grammar;
        readInGrammar(filename, grammar);
        string randomsentence, random1, random2, random3;
        for (int turn = 1; turn < 4; turn++) {
            generateSentence(grammar, randomsentence);
            if (turn == 1) {
                random1 = randomsentence;
            }
            if (turn == 2) {
                random2 = randomsentence;
            }
            if (turn == 3) {
                random3 = randomsentence;
            }
        }
        cout << "" << endl;
        cout << "1.) " << random1 << endl << endl;
        cout << "2.) " << random2 << endl << endl;
        cout << "3.) " << random3 << endl << endl;
    }
    
    cout << "Thanks for playing!" << endl;
    return 0;
}


static string getFileName() {
    while (true) {
        string filename = trim(getLine("Name of grammar file? [<return> to quit]: "));
        if (filename.empty() || isValidGrammarFilename(filename)) return filename;
        cout << "Failed to open the grammar file named \"" << filename << "\". Please try again...." << endl;
    }
}

static bool isValidGrammarFilename(string filename) {
    string normalizedFileName = getNormalizedFilename(filename);
    ifstream infile(normalizedFileName.c_str());
    return !infile.fail();
}

static string getNormalizedFilename(string filename) {
    string normalizedFileName = kGrammarsDirectory + filename;
    if (!endsWith(normalizedFileName, kGrammarFileExtension))
        normalizedFileName += kGrammarFileExtension;
    return normalizedFileName;
}


static void readInGrammar(string filename, Map<string, Vector<string> >& grammar) {
    string normalizedfilename = kGrammarsDirectory + filename;
    normalizedfilename += kGrammarFileExtension;
    ifstream inp;
    inp.open(normalizedfilename.c_str());
    if (inp.is_open() == true) {
        string line;
        Vector<string> lines;
            while (getline(inp, line)) {
                lines.add(line);// reads the whole grammar into a vector
            }
            string start = lines.get(0);
            string startlines = lines.get(2);
            Vector<string> startvector;
            startvector.add(startlines);
            grammar.put(start, startvector);
                for (int index = 0; index < lines.size(); index++) {
                    string line = lines.get(index);
                    if (line.empty()) {if (index != lines.size() - 1) {// locates non-terminals in the grammar file by locating spaces and getting positions of non-terminal, integer etc from there
                        string key = lines.get(index + 1);
                        string terminalsstring = lines.get(index + 2);
                        int terminals = stringToInteger(terminalsstring);
                        Vector<string> terminallines;// creates vector of strings for each set of lines associated with non-terminal
                        string terminalline;
                            for (int i = 0; i < terminals; i++) {// uses the integer to loop through options
                                terminalline = lines.get(index + 3 + i);
                                terminallines.add(terminalline);// loads them into vector
                                }
                        grammar.put(key, terminallines);// adds non-terminal key and vector to grammar map
                }
            }
        }
    }
}

static void generateSentence(Map<string, Vector<string> >& grammar, string& randomsentence) {
    Vector<string> start = grammar.get("<start>");
    randomsentence = start.get(0);
    TokenScanner scanner;
    scanner.addWordCharacters("<");
    scanner.addWordCharacters(">");
    scanner.addWordCharacters("-");
    while (true) {
        if (randomsentence.find('<', 0) == string::npos) {// if the < symbol for non-terminal isn't found, breaks from the loop
            break;
        }
        scanner.setInput(randomsentence);
        while (scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        int wordsize = token.size();
        if (grammar.containsKey(token)) {// iterates through sentence and finds non-terminals
            Vector<string> expansions = grammar.get(token);
                if (expansions.size() > 1) {
                    int random = randomInteger(0, expansions.size() - 1);// replaces the section of the sentence containing the non-terminal, with a random selection from the vector, if the vector contains more than one option.
                    string expand = expansions.get(random);
                    int startindex = randomsentence.find(token, 0);
                    randomsentence.replace(startindex, wordsize, expand);
                }
                else if (expansions.size() == 1) {// replaces the section of the sentence with the string from vector
                    string line = expansions.get(0);
                    int startindex = randomsentence.find(token, 0);
                    randomsentence.replace(startindex, wordsize, line);
                }
            }
        }
    }
}
    



