/**
 * File: pqueue.h
 * Original interface by eroberts
 * Last modified on Sat Nov 03 16:33:00 PST 2012 by jcain
 * ----------------------------------------------------------
 * This file provides the interface to the PQueue class, which
 * implements a simple priority queue.
 */

#ifndef _pqueue_
#define _pqueue_

#include "vector.h"
#include "types.h"
/**
 * Class: PQueue
 * -------------
 * This class that models a priority queue, which is similar to a
 * traditional queue except that the elements are inserted in
 * order of priority.  As in conventional English usage, lower
 * priority numbers correspond to higher priorities, so that a
 * priority 1 item must take precedence over a priority 2 item.
 */



class PQueue {
public:
    
    /**
     * Constructor: PQueue
     * Usage: PQueue<int> pq;
     * ----------------------
     * The constructor initializes a new priority queue containing
     * elements of the specified type.
     */
    PQueue();
    
    /**
     * Destructor: ~PQueue
     * Usage: (usually implicit)
     * -------------------------
     * The destructor deallocates storage associated with this queue.
     */
    ~PQueue();
    
    /**
     * Method: size
     * Usage: nElems = pq.size();
     * --------------------------
     * Returns the number of elements in this priority queue.
     */
    int size() const;
    
    /**
     * Method: isEmpty
     * Usage: if (pq.isEmpty()) . . .
     * ------------------------------
     * Returns true if this priority queue contains no elements,
     * and false otherwise.
     */
    bool isEmpty() const;
    
    /**
     * Method: enqueue
     * Usage: pq.enqueue(element);
     * ---------------------------------
     * This method adds element to the priority queue, using operator<
     * to decide which elements have higher priority.  Rather than relying
     * on operator< to determine priority, the interface just asks that the
     * client supply the priority.
     */
    void enqueue(Node* elem, double priority);
    
    /**
     * Method: extractMin
     * Usage: first = pq.extractMin();
     * ----------------------------
     * This method removes the highest-priority element from this queue
     * and returns it.
     */
    Node* extractMin();
    
    /**
     * Method: peek
     * Usage: first = pq.peek();
     * -------------------------
     * This method returns the value of highest-priority element in this
     * queue, without removing it.
     */
    Node* peek();
    
private:
    struct entry {
        Node* elem;
        double priority;
    };
    
	Vector<entry> entries;
};



#endif