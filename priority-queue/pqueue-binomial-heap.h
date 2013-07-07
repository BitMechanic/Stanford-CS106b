#ifndef _binomial_heap_pqueue_
#define _binomial_heap_pqueue_

#include "pqueue.h"
#include <string>
#include "vector.h"

class BinomialHeapPQueue : public PQueue {
public:
	BinomialHeapPQueue();
	~BinomialHeapPQueue();
	
	static BinomialHeapPQueue *merge(BinomialHeapPQueue *one, BinomialHeapPQueue *two);
    
   

	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
    
    
	
private:
    
    
    struct node {
        std::string word;
        Vector<node *> children;
         
    };
    
    std::string smallest;
    int key;
    node *carry;
    Vector<node *> heap;
    Vector<node *> newheap;
    int findKey() const;
    void deleteNode(int key);
    void mergeHeaps();
    void deleteTree(node * &tree);
    void deleteVector(Vector<node *> &vec);
    node *mergeTree(node * &currentp, node * &currentq);
    node *addSubTree(node * &root, node * &add);
    
    
};

#endif
