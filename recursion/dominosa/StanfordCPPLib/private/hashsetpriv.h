/*
 * File: hashsetpriv.h
 * -------------------
 * This file contains the private section of the hashset.h interface.
 * This portion of the class definition is taken out of the hashset.h
 * header so that the client need not have to see all of these
 * details.
 */

private:

   HashMap<ValueType,bool> map;        /* Map used to store the element     */
   bool removeFlag;                    /* Flag to differentiate += and -=   */

public:

/*
 * Hidden features
 * ---------------
 * The remainder of this file consists of the code required to
 * support the comma operator, deep copying, and iteration.
 * Including these methods in the public interface would make
 * that interface more difficult to understand for the average client.
 */

   HashSet & operator,(const ValueType & value) {
      if (this->removeFlag) {
         this->remove(value);
      } else {
         this->add(value);
      }
      return *this;
   }

/*
 * Method: mapAll
 * Usage: set.mapAll(fn);
 * ----------------------
 * Iterates through the elements of the set and calls <code>fn(value)</code>
 * for each one.  The values are processed in ascending order, as defined
 * by the comparison function.
 */

   void mapAll(void (*fn)(ValueType)) const;
   void mapAll(void (*fn)(const ValueType &)) const;

   template <typename FunctorType>
   void mapAll(FunctorType fn) const;

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator : public std::iterator<std::input_iterator_tag,ValueType> {

   private:

      typename HashMap<ValueType,bool>::iterator mapit;

   public:

      iterator() {
         /* Empty */
      }

      iterator(typename HashMap<ValueType,bool>::iterator it) : mapit(it) {
         /* Empty */
      }

      iterator(const iterator & it) {
         mapit = it.mapit;
      }

      iterator & operator++() {
         ++mapit;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return mapit == rhs.mapit;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      ValueType operator*() {
         return *mapit;
      }

      ValueType *operator->() {
         return mapit;
      }
   };

   iterator begin() const {
      return iterator(map.begin());
   }

   iterator end() const {
      return iterator(map.end());
   }
