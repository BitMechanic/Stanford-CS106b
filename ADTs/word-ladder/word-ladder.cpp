/**
 * File: word-ladder.cpp
 * ---------------------
 * Implements a program to find word ladders connecting pairs of words.
 */

#include <iostream>
using namespace std;

#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"
#include "queue.h"
#include <string>
#include "gevents.h"


static string getWord(Lexicon& english, string prompt);
static void processWord(string nextword, Vector<string>& newwordladder, Lexicon& usedwords, Queue<Vector<string> >& wordladders);
bool findWord(string end, Lexicon& english, Queue<Vector<string> >& wordladders, Lexicon& usedwords);
static void generateLadder(Lexicon& english, string start, string end);
static void playWordLadder(Lexicon& english);


int main() {
    Lexicon english("EnglishWords.dat");
    cout << "Welcome to Robbie's word ladder application!" << endl << endl;
    playWordLadder(english);
    cout << "Thanks for playing!" << endl;
    return 0;
}


static string getWord(Lexicon& english, string prompt) {
    while (true) {
        string response = trim(toLowerCase(getLine(prompt)));
        if (response.empty() || english.contains(response)) return response;
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}


static void processWord(string nextword, Vector<string>& newwordladder, Lexicon& usedwords, Queue<Vector<string> >& wordladders) {
    if (usedwords.contains(nextword) == false) {// Checks used words, creates new vector from copy of the old, adds english word and adds vector to the queue
        Vector<string> newestwordladder = newwordladder;
        newestwordladder.insert(0, nextword);
        usedwords.add(nextword);// adds new word to used words lexicon
        wordladders.enqueue(newestwordladder);
    }
}

bool findWord(string end, Lexicon& english, Queue<Vector<string> >& wordladders, Lexicon& usedwords) {
    for (int check = 0; check < wordladders.size(); check++) {
        Vector<string> newwordladder = wordladders.dequeue();// takes a new vector from the top of the queue
        string testword = newwordladder.get(0);
        string thisword = newwordladder.get(0);
        string solution;
        if (thisword == end) {// checks for solution
            foreach (string word in newwordladder) {
                solution = word + " " + solution;
            }
            cout << "Found ladder: " + solution << endl << endl;
            return true;
        }
        else {// creates new words by changing the letters and checking against the lexicon
            for (int i = 0; i < thisword.length(); i++) {
                testword = thisword;
                for (char alphabet = 'a'; alphabet < '{'; alphabet++) {
                    testword[i] = alphabet;
                    string nextword = testword;
                    if (english.contains(nextword.c_str())) {
                        processWord(nextword, newwordladder, usedwords, wordladders);
                    
                    }
                }
            }
        }
    }
    return false;
}

static void generateLadder(Lexicon& english, string start, string end) {
    Queue<Vector<string> > wordladders;
    Lexicon usedwords;
    usedwords.add(start);
    Vector<string> wordladder;
    wordladder.add(start);
    wordladders.enqueue(wordladder);
    while (wordladders.isEmpty() == false) {
        if (findWord(end, english, wordladders, usedwords) == true) {
            break;
        }
    }
    if (wordladders.isEmpty() == true) {
        cout << "No word ladder exists for that combination. Try again." << endl;
    }
}

static void playWordLadder(Lexicon& english) {
    while (true) {
        string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;
        if (start.length() != end.length()) {
            cout << "Those words aren't the same length, so no word ladder can be found." << endl;
            playWordLadder(english);
        }
        generateLadder(english, start, end);
    }
}

