/*
 * File: vector.h
 * --------------
 * This interface exports the <code>Vector</code> template class, which
 * provides an efficient, safe, convenient replacement for the array
 * type in C++.
 */

#ifndef _vector_h
#define _vector_h

#include <iterator>
#include "foreach.h"

/*
 * Class: Vector<ValueType>
 * ------------------------
 * This class stores an ordered list of values similar to an array.
 * It supports traditional array selection using square brackets, but
 * also supports inserting and deleting elements.
 */

template <typename ValueType>
class Vector {

public:

/*
 * Constructor: Vector
 * Usage: Vector<ValueType> vec;
 *        Vector<ValueType> vec(n, value);
 * ---------------------------------------
 * Initializes a new vector.  The default constructor creates an
 * empty vector.  The second form creates an array with <code>n</code>
 * elements, each of which is initialized to <code>value</code>;
 * if <code>value</code> is missing, the elements are initialized
 * to the default value for the type.
 */

   Vector();
   explicit Vector(int n, ValueType value = ValueType());

/*
 * Destructor: ~Vector
 * -------------------
 * Frees any heap storage allocated by this vector.
 */

   ~Vector();

/*
 * Method: size
 * Usage: int nElems = vec.size();
 * -------------------------------
 * Returns the number of elements in this vector.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (vec.isEmpty()) . . .
 * -------------------------------
 * Returns <code>true</code> if this vector contains no elements.
 */

   bool isEmpty() const;

/*
 * Method: clear
 * Usage: vec.clear();
 * -------------------
 * Removes all elements from this vector.
 */

   void clear();

/*
 * Method: get
 * Usage: ValueType val = vec.get(index);
 * --------------------------------------
 * Returns the element at the specified index in this vector.  This
 * method signals an error if the index is not in the array range.
 */

   ValueType get(int index) const;

/*
 * Method: set
 * Usage: vec.set(index, value);
 * -----------------------------
 * Replaces the element at the specified index in this vector with
 * a new value.  The previous value at that index is overwritten.
 * This method signals an error if the index is not in the array range.
 */

   void set(int index, ValueType value);

/*
 * Method: insert
 * Usage: vec.insert(0, value);
 * ----------------------------
 * Inserts the element into this vector before the specified index.
 * All subsequent elements are shifted one position to the right.  This
 * method signals an error if the index is outside the range from 0
 * up to and including the length of the vector.
 */

   void insert(int index, ValueType value);

/*
 * Method: remove
 * Usage: vec.remove(index);
 * -------------------------
 * Removes the element at the specified index from this vector.
 * All subsequent elements are shifted one position to the left.  This
 * method signals an error if the index is outside the array range.
 */

   void remove(int index);

/*
 * Method: add
 * Usage: vec.add(value);
 * ----------------------
 * Adds a new value to the end of this vector.  To ensure compatibility
 * with the <code>vector</code> class in the Standard Template Library,
 * this method is also called <code>push_back</code>.
 */

   void add(ValueType value);
   void push_back(ValueType value);

/*
 * Operator: []
 * Usage: vec[index]
 * -----------------
 * Overloads <code>[]</code> to select elements from this vector.
 * This extension enables the use of traditional array notation to
 * get or set individual elements.  This method signals an error if
 * the index is outside the array range.
 */

   ValueType & operator[](int index);
   ValueType operator[](int index) const;

/*
 * Operator: +
 * Usage: v1 + v2
 * --------------
 * Concatenates two vectors.
 */

   Vector operator+(const Vector & v2) const;

/*
 * Operator: +=
 * Usage: v1 += v2;
 *        v1 += value;
 * -------------------
 * Adds all of the elements from <code>v2</code> (or the single
 * specified value) to <code>v1</code>.  As a convenience, the
 * <code>Vector</code> package also overloads the comma operator so
 * that it is possible to initialize a vector like this:
 *
 *<pre>
 *    Vector&lt;int&gt; digits;
 *    digits += 0, 1, 2, 3, 4, 5, 6, 7, 8, 9;
 *</pre>
 */

   Vector & operator+=(const Vector & v2);
   Vector & operator+=(const ValueType & value);

/*
 * Additional Vector operations
 * ----------------------------
 * In addition to the methods listed in this interface, the Vector
 * class supports the following operations:
 *
 *   - Stream insertion using the &lt;&lt; operator
 *   - Deep copying for the copy constructor and assignment operator
 *   - Iteration using the range-based for statement, standard STL
 *     iterators, and the mapping function mapAll
 *
 * The iteration forms process the Vector in index order.
 */

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

private:

/*
 * Implementation notes: Vector data structure
 * -------------------------------------------
 * The elements of the Vector are stored in a dynamic array of
 * the specified element type.  If the space in the array is ever
 * exhausted, the implementation doubles the array capacity.
 */

/* Constants */

   static const int INITIAL_CAPACITY = 100;

/* Instance variables */

   ValueType *elements;  /* A dynamic array of the elements   */
   int capacity;         /* The allocated size of the array   */
   int count;            /* The number of elements in use     */

/* Private methods */

   void expandCapacity();

/*
 * Hidden features
 * ---------------
 * The remainder of this file consists of the code required to
 * support deep copying and iteration.  Including these methods
 * in the public interface would make that interface more
 * difficult to understand for the average client.
 */

/*
 * Deep copying support
 * --------------------
 * This copy constructor and operator= are defined to make a
 * deep copy, making it possible to pass/return vectors by value
 * and assign from one vector to another. The entire contents of
 * the vector, including all elements, are copied. Each vector
 * element is copied from the original vector to the copy using
 * assignment (operator=). Making copies is generally avoided
 * because of the expense and thus, vectors are typically passed
 * by reference, however, when a copy is needed, these operations
 * are supported.
 */

   void copyInternalData(const Vector & vec) {
      capacity = vec.count + INITIAL_CAPACITY;
      elements = new ValueType[capacity];
      for (int i = 0; i < vec.count; i++) {
         elements[i] = vec.elements[i];
      }
      count = vec.count;
   }

public:

   Vector & operator,(const ValueType & value) {
      this->add(value);
      return *this;
   }

   Vector & operator=(const Vector & rhs) {
      if (this != &rhs) {
         delete[] elements;
         copyInternalData(rhs);
      }
      return *this;
   }

   Vector(const Vector & rhs) {
      copyInternalData(rhs);
   }

/*
 * Method: mapAll
 * Usage: vec.mapAll(fn);
 * ----------------------
 * Calls the specified function on each element of the vector in
 * ascending index order.
 */

   void mapAll(void (*fn)(ValueType)) const {
      for (int i = 0; i < count; i++) {
         fn(elements[i]);
      }
   }

   void mapAll(void (*fn)(const ValueType &)) const {
      for (int i = 0; i < count; i++) {
         fn(elements[i]);
      }
   }

   template <typename FunctorType>
   void mapAll(FunctorType fn) const {
      for (int i = 0; i < count; i++) {
         fn(elements[i]);
      }
   }

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator :
      public std::iterator<std::random_access_iterator_tag, ValueType> {

   private:
      const Vector *vp;
      int index;

   public:

      iterator() {
         this->vp = NULL;
      }

      iterator(const iterator & it) {
         this->vp = it.vp;
         this->index = it.index;
      }

      iterator(const Vector *vp, int index) {
         this->vp = vp;
         this->index = index;
      }

      iterator & operator++() {
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      iterator & operator--() {
         index--;
         return *this;
      }

      iterator operator--(int) {
         iterator copy(*this);
         operator--();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return vp == rhs.vp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      bool operator<(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index < rhs.index;
      }

      bool operator<=(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index <= rhs.index;
      }

      bool operator>(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index > rhs.index;
      }

      bool operator>=(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index >= rhs.index;
      }

      iterator operator+(const int & rhs) {
         return iterator(vp, index + rhs);
      }

      iterator operator+=(const int & rhs) {
         index += rhs;
         return *this;
      }

      iterator operator-(const int & rhs) {
         return iterator(vp, index - rhs);
      }

      iterator operator-=(const int & rhs) {
         index -= rhs;
         return *this;
      }

      int operator-(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index - rhs.index;
      }

      ValueType & operator*() {
         return vp->elements[index];
      }

      ValueType *operator->() {
         return &vp->elements[index];
      }

      ValueType & operator[](int k) {
         return vp->elements[index + k];
      }

   };

   iterator begin() const {
      return iterator(this, 0);
   }

   iterator end() const {
      return iterator(this, count);
   }

};

#include <iostream>

extern void error(std::string msg);

/*
 * Implementation notes: Vector constructor and destructor
 * -------------------------------------------------------
 * The constructor allocates storage for the dynamic array
 * and initializes the other fields of the object.  The
 * destructor frees the memory used for the array.
 */

template <typename ValueType>
Vector<ValueType>::Vector() {
   count = 0;
   capacity = INITIAL_CAPACITY;
   elements = new ValueType[capacity];
}

template <typename ValueType>
Vector<ValueType>::Vector(int n, ValueType value) {
   count = capacity = n;
   elements = new ValueType[n];
   for (int i = 0; i < n; i++) {
      elements[i] = value;
   }
}

template <typename ValueType>
Vector<ValueType>::~Vector() {
   delete[] elements;
}

/*
 * Implementation notes: Vector methods
 * ------------------------------------
 * The basic Vector methods are straightforward and should require
 * no detailed documentation.
 */

template <typename ValueType>
int Vector<ValueType>::size() const {
   return count;
}

template <typename ValueType>
bool Vector<ValueType>::isEmpty() const {
   return count == 0;
}

template <typename ValueType>
void Vector<ValueType>::clear() {
   delete[] elements;
   count = 0;
   capacity = INITIAL_CAPACITY;
   elements = new ValueType[capacity];
}

template <typename ValueType>
ValueType Vector<ValueType>::get(int index) const {
   if (index < 0 || index >= count) error("get: index out of range");
   return elements[index];
}

template <typename ValueType>
void Vector<ValueType>::set(int index, ValueType value) {
   if (index < 0 || index >= count) error("set: index out of range");
   elements[index] = value;
}

/*
 * Implementation notes: insert, remove, add
 * -----------------------------------------
 * These methods must shift the existing elements in the array to
 * make room for a new element or to close up the space left by a
 * deleted one.
 */

template <typename ValueType>
void Vector<ValueType>::insert(int index, ValueType value) {
   if (count == capacity) expandCapacity();
   if (index < 0 || index > count) {
      error("insert: index out of range");
   }
   for (int i = count; i > index; i--) {
      elements[i] = elements[i - 1];
   }
   elements[index] = value;
   count++;
}

template <typename ValueType>
void Vector<ValueType>::remove(int index) {
   if (index < 0 || index >= count) error("remove: index out of range");
   for (int i = index; i < count - 1; i++) {
      elements[i] = elements[i + 1];
   }
   count--;
}

template <typename ValueType>
void Vector<ValueType>::add(ValueType value) {
   insert(count, value);
}

template <typename ValueType>
void Vector<ValueType>::push_back(ValueType value) {
   insert(count, value);
}

/*
 * Implementation notes: Vector selection
 * --------------------------------------
 * The following code implements traditional array selection using
 * square brackets for the index.
 */

template <typename ValueType>
ValueType & Vector<ValueType>::operator[](int index) {
   if (index < 0 || index >= count) error("Selection index out of range");
   return elements[index];
}
template <typename ValueType>
ValueType Vector<ValueType>::operator[](int index) const {
   if (index < 0 || index >= count) error("Selection index out of range");
   return elements[index];
}

template <typename ValueType>
Vector<ValueType> Vector<ValueType>::operator+(const Vector & v2) const {
   Vector<ValueType> vec = *this;
   foreach (ValueType value in v2) {
      vec.add(value);
   }
   return vec;
}

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator+=(const Vector & v2) {
   foreach (ValueType value in v2) {
      *this += value;
   }
   return *this;
}

template <typename ValueType>
Vector<ValueType> & Vector<ValueType>::operator+=(const ValueType & value) {
   this->add(value);
   return *this;
}

/*
 * Implementation notes: expandCapacity
 * ------------------------------------
 * This function doubles the array capacity, copies the old elements
 * into the new array, and then frees the old one.
 */

template <typename ValueType>
void Vector<ValueType>::expandCapacity() {
   capacity = capacity * 2;
   ValueType *array = new ValueType[capacity];
   for (int i = 0; i < count; i++) {
      array[i] = elements[i];
   }
   delete[] elements;
   elements = array;
}

/*
 * Operator: <<
 * Usage: cout << vec;
 * -------------------
 * Implements the insertion operator for the Vector class.  The elements
 * of the Vector are surrounded by curly braces and separated by commas.
 */

template <typename ValueType>
std::ostream & operator<<(ostream & os, const Vector<ValueType> & vec) {
   os << "{";
   int len = vec.size();
   for (int i = 0; i < len; i++) {
      if (i > 0) os << ", ";
      os << vec[i];
   }
   return os << "}";
}

#endif
