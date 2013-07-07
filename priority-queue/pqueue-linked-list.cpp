#include "pqueue-linked-list.h"
#include "error.h"


using namespace std;

LinkedListPQueue::LinkedListPQueue() {
    head = tail = NULL;
}

LinkedListPQueue::~LinkedListPQueue() {
    cellT *cp = head;
    while (cp != NULL) {
        cellT *del = cp->next;
        delete cp;
        cp = del;
    }
}

string LinkedListPQueue::peek() const {
    if (isEmpty()) error("Empty queue");
    string first = head->word;
    return first;
}

string LinkedListPQueue::extractMin() {
    if (isEmpty()) error("Empty queue");
    string first = head->word;
    cellT *dequeued = head;
    head = head->next;
    delete dequeued;
    logSize--;
    return first;
    
}

void LinkedListPQueue::enqueue(const string& elem) {
    cellT *newCell = new cellT;
    newCell->word = elem;
        if (isEmpty()) {
            newCell->prev = NULL;
            newCell->next = NULL;
            head = tail = newCell;
    }
        else if (elem <= head->word) {
            newCell->next = head;
            head->prev = newCell;
            newCell->prev = NULL;
            head = newCell;
    }
        else if (elem >= tail->word) {
            tail->next = newCell;
            newCell->prev = tail;
            newCell->next = NULL;
            tail = newCell;
    }
        else {
            for (cursorA = tail; cursorA != NULL; cursorA = cursorA->prev) {
                if (cursorA->word <= elem) {
                    cursorB = tail;
                    while (cursorB->prev != cursorA) {
                        cursorB = cursorB->prev;
            }
                    cursorB->prev = newCell;
                    newCell->prev = cursorA;
                    newCell->next = cursorB;
                    cursorA->next = newCell;
                    break;
            }
        }
    }
    logSize++;
}

LinkedListPQueue *LinkedListPQueue::merge(LinkedListPQueue *one, LinkedListPQueue *two) {
	LinkedListPQueue *result = new LinkedListPQueue;
    for (int i = 0; i < 1000; i++) {
        string test1 = one->extractMin();
        string test2 = two->extractMin();
        result->enqueue(test1);
        result->enqueue(test2);
    }
	return result;
}



