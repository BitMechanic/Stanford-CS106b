/**
 * File: generate-mnemonics.cpp
 * ----------------------------
 * This is an application that compiles phone numbers (or, more generally,
 * numbers) to mnemonics, where the digit-to-letter mappins are consistent
 * with those listed on a traditional telephone keypad.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
using namespace std;

#include "console.h"
#include "simpio.h"  // for getLine
#include "vector.h"  // for the Vector class template
#include "map.h"     // for the Map class template

static void buildMappings(Map<char, string>& mappings);
static bool isAllPositiveDigits(const string& response);
static string getPhoneNumber();
static void generateMnemonics(string rest, Map<char, string>& mappings, Vector<string>& mnemonics);
static void setUpMnemonics(const string& number, Map<char, string>& mappings, Vector<string>& mnemonics);
    
int main() {
    Map<char, string> mappings;
    buildMappings(mappings);
    while (true) {
        string number = getPhoneNumber();
        if (number.empty()) break;
        Vector<string> mnemonics;
        setUpMnemonics(number, mappings, mnemonics);
        cout << "These are the possible mnemonics: " << endl << endl;
        int count = 0;
        foreach (string mnemonic in mnemonics) {
            cout << "  " << mnemonic;
            count = (count + 1) % 9;
            if (count % 9 == 0) cout << endl;
        }
        cout << endl;
    }
    
    return 0;
}

static void setUpMnemonics(const string& number, Map<char, string>& mappings, Vector<string>& mnemonics) {
    char startkey = number[0];
    string rest = number.substr(1);
    string start = mappings.get(startkey);
    for (int i = 0; i < start.size(); i++) {
        string stub = start.substr(i, 1);// turn the start string into stubs
        mnemonics.add(stub);// and add to the mnemonics vector
        }
    generateMnemonics(rest, mappings, mnemonics);
}

static void generateMnemonics(string rest, Map<char, string>& mappings, Vector<string>& mnemonics) {
    if (rest == "") {// base case- wait till "rest" (all the keys) is gone and then return
        return;
    } else {
        Vector<string> temporary;// if results are stored in mnemonics during the loop it'll be infinite
        char key = rest[0];
        string next = mappings.get(key);
            if (rest.size() > 1) {// remove the current number from the string of keys
                rest = rest.substr(1);
        }
            else {
                rest = "";
        }
        for (int stub = 0; stub < mnemonics.size(); stub++) {// pull the stubs from mnemonics
            string current = mnemonics.get(stub);
            for (int nextone = 0; nextone < next.length(); nextone++) {// cycle through next characters and add to the stubs
                string character = next.substr(nextone, 1);
                string result = current + character;
                temporary.add(result);// add results to temporary
            }
        }
        mnemonics = temporary;// copy temporary on to mnemonics
        generateMnemonics(rest, mappings, mnemonics);
    }
}
                                  
static string getPhoneNumber() {
    while (true) {
        string response = getLine("Enter a string of digits [or hit <enter> if you're done]: ");
        if (isAllPositiveDigits(response)) return response;
        cout << "Whatever you enter, make sure it includes only digit characters in ['2', '9'].  ";
        cout << "Please try again." << endl;
    }
}

static bool isAllPositiveDigits(const string& response) {
    for (int i = 0; i < response.size(); i++) {
        if (response[i] < '2' || response[i] > '9') {
            return false;
        }
    }
                                      
    return true;
}
                                  
static void buildMappings(Map<char, string>& mappings) {
    const string options[] = {
        "ABC", "DEF", "GHI", "JKL",
        "MNO", "PQRS", "TUV", "WXYZ"
        };
                                      
    for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
        mappings['2' + i] = options[i];
    }
}
