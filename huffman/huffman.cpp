/**
 * File: huffman.cpp
 * -------------------
 * Huffman main module.
 */


#include "simpio.h"
#include "console.h"

#include "encoding.h"
#include "bstream.h"
#include <string>
#include "strlib.h"
using namespace std;

static bool responseIsAffirmative(const string& prompt);
string getFileName(int turn);
void compressFile(string filename);
void decompressFile(string decompname);


int main() {
    
    setConsoleSize(1000, 400);
    setConsoleFont("Ariel-12");
    cout << "Wellcome to Robbie's Huffman compression program!" << endl;
    cout << "This program uses the Huffman coding algorithm for compression." << endl;
    cout << "Any file can be compressed by using this method, often with substantial" << endl;
    cout << "savings. Decompression will faithfully reproduce the original." << endl << endl;
    if (responseIsAffirmative("Would you like to compress or decompress another file? ")) {
        if (responseIsAffirmative("Are we compressing? ")) {
            string filename = getFileName(1);
            compressFile(filename);
            
        }
        else {
            string decompname = getFileName(3);
            decompressFile(decompname);
        }
    }

    return 0;
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

void compressFile(string filename) {
    ibstream infile;
    obstream outfile;
    
    infile.open(filename.c_str());
    if (infile.fail()) {
        cout << "Couldn't open infile." << endl;
    }
    
    string compname = getFileName(2);
    
    outfile.open(compname.c_str());
    if (infile.fail()) {
        cout << "Couldn't open outfile." << endl;
    }

    Encoding compressfile;
    compressfile.compress(infile, outfile);
    //map<int, string>::iterator iter;
    //string encodings = "";
    //foreach(int key in compressfile.referenceTable) {
    //    iter = compressfile.referenceTable.find(key);
    //    string freq = iter->second;
    //    encodings = encodings + "Encoding: " + freq + " ";
    //}
    //cout << encodings << endl << endl;
}

void decompressFile(string decompname) {
    ibstream infile;
    obstream outfile;
    
    infile.open(decompname.c_str());
    if (infile.fail()) {
        cout << "Couldn't open infile." << endl;
    }
    
    string compname = getFileName(4);
    
    outfile.open(compname.c_str());
    if (infile.fail()) {
        cout << "Couldn't open outfile." << endl;
    }
    
    Encoding decompressfile;
    decompressfile.decompress(infile, outfile);
    //int enc = decompressfile.encoding.size();
    //string encodingsize = integerToString(enc);
    //cout << "Size of vector: " + encodingsize << endl << endl;
    //string code = "";
    //for (int i = 0; i < enc; i++) {
    //   int bit =  decompressfile.encoding.get(i);
    //    string bitstring = integerToString(bit);
    //    code = code + " " + bitstring;
    //}
    //cout << "This is the entire encoding: " + code << endl << endl;
}

string getFileName(int turn) {
    
    string filename;
    if (turn == 1) {
        cout << "Enter the name of the file to compress: ";
        filename = getLine();
    }
    else if (turn == 2) {
        cout << "Enter the name we should give the compressed file: ";
        filename = getLine();
    }
    else if (turn == 3) {
        cout << "Enter the name of the file to decompress: ";
        filename = getLine();
    }
    else if (turn == 4) {
        cout << "Enter the name we should give to the decompressed file: ";
        filename = getLine();
    }
    if (filename == "") {
        cout << "That file couldn't be found. Please try again." << endl;
    }
        
    return filename;
}