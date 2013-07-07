/*
 * File: stack.h
 * -------------
 * This interface exports the <code>Stack</code> class, which implements
 * a collection that processes values in a last-in/first-out (LIFO) order.
 */

#ifndef _stack_h
#define _stack_h

#include "vector.h"

/*
 * Class: Stack<ValueType>
 * -----------------------
 * This class models a linear structure called a <i>stack</i>
 * in which values are added and removed only from one end.
 * This discipline gives rise to a last-in/first-out behavior (LIFO)
 * that is the defining feature of stacks.  The fundamental stack
 * operations are <code>push</code> (add to top) and <code>pop</code>
 * (remove from top).
 */

template <typename ValueType>
class Stack {

public:

/*
 * Constructor: Stack
 * Usage: Stack<ValueType> stack;
 * ------------------------------
 * Initializes a new empty stack.
 */

   Stack();

/*
 * Destructor: ~Stack
 * ------------------
 * Frees any heap storage associated with this stack.
 */

   ~Stack();

/*
 * Method: size
 * Usage: int n = stack.size();
 * ----------------------------
 * Returns the number of values in this stack.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (stack.isEmpty()) . . .
 * ---------------------------------
 * Returns <code>true</code> if this stack contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: stack.clear();
 * ---------------------
 * Removes all elements from this stack.
 */

   void clear();

/*
 * Method: push
 * Usage: stack.push(value);
 * -------------------------
 * Pushes the specified value onto this stack.
 */

   void push(ValueType value);

/*
 * Method: pop
 * Usage: ValueType top = stack.pop();
 * -----------------------------------
 * Removes the top element from this stack and returns it.  This
 * method signals an error if called on an empty stack.
 */

   ValueType pop();

/*
 * Method: peek
 * Usage: ValueType top = stack.peek();
 * ------------------------------------
 * Returns the value of top element from this stack, without removing
 * it.  This method signals an error if called on an empty stack.  For
 * compatibility with the STL classes, this method is also exported
 * under the name <code>top</code>, in which case it returns the value
 * by reference.
 */

   ValueType peek() const;
   ValueType & top();

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

/*
 * Implementation notes: Stack data structure
 * ------------------------------------------
 * The easiest way to implement a stack is to store the elements in a
 * Vector.  Doing so means that the problems of dynamic memory allocation
 * and copy assignment are already solved by the implementation of the
 * underlying Vector class.
 */

private:
   Vector<ValueType> elements;

};

extern void error(std::string msg);

/*
 * Stack class implementation
 * --------------------------
 * The Stack is internally managed using a Vector.  This layered design
 * makes the implementation extremely simple, to the point that most
 * methods can be implemented in as single line.
 */

template <typename ValueType>
Stack<ValueType>::Stack() {
   /* Empty */
}

template <typename ValueType>
Stack<ValueType>::~Stack() {
   /* Empty */
}

template <typename ValueType>
int Stack<ValueType>::size() const {
   return elements.size();
}

template <typename ValueType>
bool Stack<ValueType>::isEmpty() const {
   return size() == 0;
}

template <typename ValueType>
void Stack<ValueType>::push(ValueType value) {
   elements.add(value);
}

template <typename ValueType>
ValueType Stack<ValueType>::pop() {
   if (isEmpty()) error("pop: Attempting to pop an empty stack");
   ValueType top = elements[elements.size() - 1];
   elements.remove(elements.size() - 1);
   return top;
}

template <typename ValueType>
ValueType Stack<ValueType>::peek() const {
   if (isEmpty()) error("peek: Attempting to peek at an empty stack");
   return elements.get(elements.size() - 1);
}

template <typename ValueType>
ValueType & Stack<ValueType>::top() {
   if (isEmpty()) error("top: Attempting to read top of an empty stack");
   return elements[elements.size() - 1];
}

template <typename ValueType>
void Stack<ValueType>::clear() {
   elements.clear();
}

#endif
