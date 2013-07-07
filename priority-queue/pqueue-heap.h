#ifndef _binary_heap_pqueue_
#define _binary_heap_pqueue_

#include "pqueue.h"
#include <string>

class HeapPQueue : public PQueue {
public:
	HeapPQueue();
	~HeapPQueue();
	
	static HeapPQueue *merge(HeapPQueue *one, HeapPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
    
private:
    static const int START_CAPACITY = 1000;
    int capacity;
    std::string *heap;
    void bubbleUp(int logSize);
    void expandCapacity();
    void heapIfy(int node);
    void reverseHeapify(int head, int tail);
    void add(std::string word);
    std::string getAt(int index);

};

#endif