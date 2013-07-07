#include "pqueue-heap.h"
#include "error.h"
using namespace std;

HeapPQueue::HeapPQueue() {
    capacity = START_CAPACITY;
    heap = new string[capacity];
    
}
HeapPQueue::~HeapPQueue() {
    delete[] heap;
    
}

string HeapPQueue::peek() const {
    string first = heap[1];
	return first;
}

string HeapPQueue::extractMin() {
    string first = heap[1];
        if (first == "") error("Attempting to extract from empty queue");
            string last = heap[logSize];
            heap[1] = last;//replace first with last word
            heap[logSize] = "";//erase last word from array
            logSize--;//decrease logSize
            heapIfy(1);
            return first;
}

void HeapPQueue::heapIfy(int node) {
    if (node >= logSize) return;// base case
    
    int L = node * 2;// left and right nodes
    int R = (node * 2) + 1;
    int smallest = 0;
        if (L <= logSize && heap[node] > heap[L]) {// check in bounds and assign smallest if left is smaller than node
            smallest = L;
    }
        else smallest = node;
    
        if (R <= logSize && heap[R] < heap[smallest]) {// check in bounds etc...
            smallest = R;
    }
        if (smallest != node) {// if node isnt smallest swap with smallest
            string swap = heap[smallest];
            heap[smallest] = heap[node];
            heap[node] = swap;
    }
        else if (smallest == node) return;// or return
        
    heapIfy(smallest);// recursively heapify
}

void HeapPQueue::enqueue(const string& elem) {
    if (logSize + 10 == capacity) {
        expandCapacity();
    }
    logSize++;//Set logSize to 1 to start, so can use logSize for heap calculations
    heap[logSize] = elem;//first element set to index 1, not using index 0 at all
    bubbleUp(logSize);
}

void HeapPQueue::expandCapacity() {
    capacity *= 2;
    string *oldheap = heap;
    heap = new string[capacity];
        for (int i = 1; i <= logSize; i++) {
            heap[i] = oldheap[i];
    }
    
    delete[] oldheap;
}

void HeapPQueue::bubbleUp(int i) {
    if (i / 2 == 0) return;// base case = index 1
    
    string insert = heap[i];
    string node = heap[i / 2];
        if (insert >= node) return;// return if bubbled up to the right position
        heap[i] = node;// swap
        heap[i / 2] = insert;
        bubbleUp(i / 2);// recursively bubbleUp
}

HeapPQueue *HeapPQueue::merge(HeapPQueue *one, HeapPQueue *two) {
    HeapPQueue *mergeheap = new HeapPQueue;
    int size1 = one->logSize;
    int size2 = two->logSize;
    mergeheap->capacity = size1 + size2;
    mergeheap->expandCapacity();// create empty array with enough capacity
    
    for (int i = 1; i <= size1; i++) {// two for loops in case one and two are different sizes
        string copy1 = one->getAt(i);
        mergeheap->add(copy1);
    }
    
    for (int y = 1; y <= size2; y++) {
        string copy2 = two->getAt(y);
        mergeheap->add(copy2);
    }

    int tail = mergeheap->logSize;
    int head = tail / 2;
    mergeheap->reverseHeapify(head, tail);// heapify 
    return mergeheap;
}

void HeapPQueue::add(string word) {
    heap[logSize + 1] = word;
    logSize++;
}
 
string HeapPQueue::getAt(int index) {
    string word = heap[index];
    return word;
}

void HeapPQueue::reverseHeapify(int head, int tail) {
    int newtail = head;
    int newhead = head / 2;// each segment is a generation of nodes
    if (newhead / 2 < 1) return;
    
        for (int i = newhead; i <= newtail; i++) {// cycle through each segment and heapify each node
            heapIfy(i);
    }
    reverseHeapify(newhead, newtail);
}
