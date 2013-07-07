#include "pqueue-vector.h"

using namespace std;

VectorPQueue::VectorPQueue() {
    
}

VectorPQueue::~VectorPQueue() {
    
}

string VectorPQueue::peek() const {
    if(isEmpty()) {
        error("peek; Attempting to peek at an empty queue");
    }
    string result = pQueue.get(0);
	return result;
}

string VectorPQueue::extractMin() {
    if (isEmpty()) {
        error("extractmin; Queue is empty");
    }
    int min = 0;
    string minimum = pQueue.get(0);
	for (int i= 1; i < logSize; i++) {
        string check = pQueue.get(i);
        if (check < minimum) {
            min = i;
            minimum = check;
        }
    }
    pQueue.remove(min);
    logSize--;
	return minimum;
}

void VectorPQueue::enqueue(const string& elem) {
	pQueue.add(elem);
    logSize++;
}

VectorPQueue *VectorPQueue::merge(VectorPQueue *one, VectorPQueue *two) {
    VectorPQueue *result = new VectorPQueue;
    for (int i = 0; i < 1000; i++) {
        string test1 = one->extractMin();
        string test2 = two->extractMin();
        result->enqueue(test1);
        result->enqueue(test2);
        }
	return result;
}
