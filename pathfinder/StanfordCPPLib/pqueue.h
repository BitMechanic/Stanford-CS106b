/*
 * File: pqueue.h
 * --------------
 * This interface exports the <code>PriorityQueue</code> class, a
 * collection in which values are processed in priority order.
 */

#ifndef _pqueue_h
#define _pqueue_h

#include "vector.h"

/*
 * Class: PriorityQueue<ValueType>
 * -------------------------------
 * This class models a linear structure called a <i>priority&nbsp;queue</i>
 * in which values are processed in order of priority.  As in conventional
 * English usage, lower priority numbers correspond to higher effective
 * priorities, so that a priority 1 item takes precedence over a
 * priority 2 item.
 */

template <typename ValueType>
class PriorityQueue {

public:

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue<ValueType> pq;
 * -----------------------------------
 * Initializes a new priority queue, which is initially empty.
 */

   PriorityQueue();

/*
 * Destructor: ~PriorityQueue
 * --------------------------
 * Frees any heap storage associated with this priority queue.
 */

   ~PriorityQueue();

/*
 * Method: size
 * Usage: int n = pq.size();
 * -------------------------
 * Returns the number of values in the priority queue.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) . . .
 * ------------------------------
 * Returns <code>true</code> if the priority queue contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from the priority queue.
 */

   void clear();

/*
 * Method: enqueue
 * Usage: pq.enqueue(value, priority);
 * -----------------------------------
 * Adds <code>value</code> to the queue with the specified priority.
 * Lower priority numbers correspond to higher priorities, which
 * means that all priority 1 elements are dequeued before any
 * priority 2 elements.
 */

   void enqueue(ValueType value, double priority);

/*
 * Method: dequeue
 * Usage: ValueType first = pq.dequeue();
 * --------------------------------------
 * Removes and returns the highest priority value.  If multiple
 * entries in the queue have the same priority, those values are
 * dequeued in the same order in which they were enqueued.
 */

   ValueType dequeue();

/*
 * Method: peek
 * Usage: ValueType first = pq.peek();
 * -----------------------------------
 * Returns the value of highest priority in the queue, without
 * removing it.
 */

   ValueType peek() const;

/*
 * Method: front
 * Usage: ValueType first = pq.front();
 * ------------------------------------
 * Returns the first value in the queue by reference.
 */

   ValueType & front();

/*
 * Method: back
 * Usage: ValueType last = pq.back();
 * ----------------------------------
 * Returns the last value in the queue by reference.
 */

   ValueType & back();

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

/*
 * Implementation notes: PriorityQueue data structure
 * --------------------------------------------------
 * The PriorityQueue class is implemented using a data structure called
 * a heap.
 */

private:

/* Type used for each heap entry */

   struct HeapEntry {
      ValueType value;
      double priority;
      long sequence;
   };

/* Instance variables */

   Vector<HeapEntry> heap;
   long enqueueCount;
   int backIndex;
   int count;
   int capacity;

/* Private function prototypes */

   void enqueueHeap(ValueType & value, double priority);
   ValueType dequeueHeap();
   bool takesPriority(int i1, int i2);
   void swapHeapEntries(int i1, int i2);

};

extern void error(std::string msg);

template <typename ValueType>
PriorityQueue<ValueType>::PriorityQueue() {
   clear();
}

/*
 * Implementation notes: ~PriorityQueue destructor
 * -----------------------------------------------
 * All of the dynamic memory is allocated in the Vector class,
 * so no work is required at this level.
 */

template <typename ValueType>
PriorityQueue<ValueType>::~PriorityQueue() {
   /* Empty */
}

template <typename ValueType>
int PriorityQueue<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::clear() {
   heap.clear();
   count = 0;
}

template <typename ValueType>
void PriorityQueue<ValueType>::enqueue(ValueType value, double priority) {
   if (count == heap.size()) heap.add(HeapEntry());
   int index = count++;
   heap[index].value = value;
   heap[index].priority = priority;
   heap[index].sequence = enqueueCount++;
   if (index == 0 || takesPriority(backIndex, index)) backIndex = index;
   while (index > 0) {
      int parent = (index - 1) / 2;
      if (takesPriority(parent, index)) break;
      swapHeapEntries(parent, index);
      index = parent;
   }
}

/*
 * Implementation notes: dequeue, peek
 * -----------------------------------
 * These methods must check for an empty queue and report an error
 * if there is no first element.
 */

template <typename ValueType>
ValueType PriorityQueue<ValueType>::dequeue() {
   if (count == 0) error("dequeue: Attempting to dequeue an empty queue");
   count--;
   bool wasBack = (backIndex == count);
   ValueType value = heap[0].value;
   swapHeapEntries(0, count);
   int index = 0;
   while (true) {
      int left = 2 * index + 1;
      int right = 2 * index + 2;
      if (left >= count) break;
      int child = left;
      if (right < count && takesPriority(right, left)) child = right;
      if (takesPriority(index, child)) break;
      swapHeapEntries(index, child);
      index = child;
   }
   if (wasBack) backIndex = index;
   return value;
}

template <typename ValueType>
ValueType PriorityQueue<ValueType>::peek() const {
   if (count == 0) error("peek: Attempting to peek at an empty queue");
   return heap.get(0).value;
}

template <typename ValueType>
ValueType & PriorityQueue<ValueType>::front() {
   if (count == 0) error("front: Attempting to read front of an empty queue");
   return heap.get(0).value;
}

template <typename ValueType>
ValueType & PriorityQueue<ValueType>::back() {
   if (count == 0) error("back: Attempting to read back of an empty queue");
   return heap.get(backIndex).value;
}

template <typename ValueType>
bool PriorityQueue<ValueType>::takesPriority(int i1, int i2) {
   if (heap[i1].priority < heap[i2].priority) return true;
   if (heap[i1].priority > heap[i2].priority) return false;
   return (heap[i1].sequence < heap[i2].sequence);
}

template <typename ValueType>
void PriorityQueue<ValueType>::swapHeapEntries(int i1, int i2) {
   HeapEntry entry = heap[i1];
   heap[i1] = heap[i2];
   heap[i2] = entry;
}

#endif
