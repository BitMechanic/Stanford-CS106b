/**
 * File: encoding.h
 * ----------------
 * Defines the Encoding class to manage all aspects of the
 * Huffman compression and decompression algorithms.
 */

#ifndef _encoding_
#define _encoding_

#include "bstream.h"
#include "types.h"
#include <map>
#include "pqueue.h"
#include "vector.h"


class Encoding {
    
public:
    
    void compress(ibstream& infile, obstream& outfile);
    void decompress(ibstream& infile, obstream& outfile);
    

private:
    
    PQueue huffqueue;
    Node *currentroot;
    Node *treeroot;
    map<int, int> frequencyTable;
    map<int, std::string> referenceTable;
    int leafcount;
    
    void getFrequency(ibstream& infile);
    void enqueueNodes();
    void buildTree(int leaves);
    void createReferenceTable(int leaves);
    void tracePaths(Node *root, std::string path, int leaves);
    void encodeFile(ibstream& infile, obstream& outfile, int leaves);
    void deleteTree(Node *root);
    void writeHeader(obstream& outfile, int leaves);
    void extractHeader(ibstream& infile);
    void decodeFile(ibstream& infile, obstream& outfile, int filesz);
    
};

#endif
