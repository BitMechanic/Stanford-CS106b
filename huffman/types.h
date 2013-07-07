//
//  types.h
//  huffman
//
//  Created by Robbie on 20/05/2013.
//
//

#ifndef huffman_types_h
#define huffman_types_h



const int VOID = 257;


struct Node {
   
    int character;
    
    Node *zero;
    
    Node *one;
    
    int frequency;
    
};



#endif
