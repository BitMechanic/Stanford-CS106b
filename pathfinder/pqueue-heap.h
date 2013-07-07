//
//  pqueue-heap.h
//  pathfinder
//
//  Created by Robbie on 08/06/2013.
//
//

#ifndef __pathfinder__pqueue_heap__
#define __pathfinder__pqueue_heap__


#include <string>
#include "cmpfn.h"
#include <iostream>



template <typename ElemType>
class HeapPQueue {
public:
    
	HeapPQueue<ElemType>() {
        capacity = START_CAPACITY;
        heap = new ElemType[capacity];
        logSize = 0;
        
    }
    
	~HeapPQueue<ElemType>() {
        delete[] heap;
    }
	
	static HeapPQueue *merge(HeapPQueue *one, HeapPQueue *two, int (*cmp) (ElemType, ElemType)) {
        HeapPQueue<ElemType> *mergeheap = new HeapPQueue<ElemType>;
        int size1 = one->logSize;
        int size2 = two->logSize;
        mergeheap->capacity = size1 + size2;
        mergeheap->expandCapacity();// create empty array with enough capacity
        
        for (int i = 1; i <= size1; i++) {// two for loops in case one and two are different sizes
            ElemType copy1 = one->getAt(i);
            mergeheap->add(copy1);
        }
        
        for (int y = 1; y <= size2; y++) {
            ElemType copy2 = two->getAt(y);
            mergeheap->add(copy2);
        }
        
        int tail = mergeheap->logSize;
        int head = tail / 2;
        mergeheap->reverseHeapify(head, tail, cmp);// heapify
        return mergeheap;
    }

    
	
	void enqueue(const ElemType &elem, int (*cmp) (ElemType, ElemType)) {
        if (logSize + 10 == capacity) {
            expandCapacity();
        }
        logSize++;//Set logSize to 1 to start, so can use logSize for heap calculations
        heap[logSize] = elem;//first element set to index 1, not using index 0 at all
        bubbleUp(logSize, cmp);
    }

    
    
    ElemType extractMin(int (*cmp) (ElemType, ElemType)) {
        ElemType first = heap[1];
        //if (first == "") error("Attempting to extract from empty queue");
        ElemType last = heap[logSize];
        heap[1] = last;//replace first with last word
        //heap[logSize] = "";//erase last word from array
        logSize--;//decrease logSize
        heapIfy(1, cmp);
        return first;
    }
    
    ElemType peek() const {
        ElemType first = heap[1];
        return first;
    }
    
    int size() {
        return logSize;
    }
    
    
private:
  
    void bubbleUp(int i, int (*cmp) (ElemType, ElemType)) {
        if (i / 2 == 0) return;// base case = index 1
        
        ElemType insert = heap[i];
        ElemType node = heap[i / 2];
    
        if (cmp(insert, node) != -1) return;// return if bubbled up to the right position
        heap[i] = node;// swap
        heap[i / 2] = insert;
        bubbleUp(i / 2, cmp);// recursively bubbleUp
    }


    void expandCapacity() {
        capacity *= 2;
        ElemType *oldheap = heap;
        heap = new ElemType[capacity];
        for (int i = 1; i <= logSize; i++) {
            heap[i] = oldheap[i];
        }
        
        delete[] oldheap;
    }

    
    void heapIfy(int node, int (*cmp) (ElemType, ElemType)) {// need some sort of comp function which gets sent pointer to comp plus
        if (node >= logSize) return;// base case
        
        int L = node * 2;// left and right nodes
        int R = (node * 2) + 1;
        int smallest = 0;
        
        if (L <= logSize && cmp(heap[node], heap[L]) == 1) {// check in bounds and assign smallest if left is smaller than node
            smallest = L;
        }
        else smallest = node;
        
        if (R <= logSize && cmp(heap[R], heap[smallest]) == -1) {// check in bounds etc...
            smallest = R;
        }
        if (smallest != node) {// if node isnt smallest swap with smallest
            ElemType swap = heap[smallest];
            heap[smallest] = heap[node];
            heap[node] = swap;
        }
        else if (smallest == node) return;// or return
        
        heapIfy(smallest, cmp);// recursively heapify
    }

    
    void reverseHeapify(int head, int tail, int (*cmp) (ElemType, ElemType)) {
        int newtail = head;
        int newhead = head / 2;// each segment is a generation of nodes
        if (newhead / 2 < 1) return;
        
        for (int i = newhead; i <= newtail; i++) {// cycle through each segment and heapify each node
            heapIfy(i, cmp);
        }
        reverseHeapify(newhead, newtail, cmp);
    }
    
    void add(ElemType word) {
        heap[logSize + 1] = word;
        logSize++;
    }
    
    ElemType getAt(int index) {
        ElemType word = heap[index];
        return word;
    }
    
    int logSize;
    static const int START_CAPACITY = 1000;
    int capacity;
    ElemType *heap;

    
};



#endif /* defined(__pathfinder__pqueue_heap__) */
