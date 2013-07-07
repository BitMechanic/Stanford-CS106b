/*
 * File: setimpl.cpp
 * -----------------
 * This file contains the implementation of the set.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _set_h

template <typename ValueType>
Set<ValueType>::Set() {
   /* Empty */
}

template <typename ValueType>
Set<ValueType>::~Set() {
   /* Empty */
}

template <typename ValueType>
int Set<ValueType>::size() const {
   return map.size();
}

template <typename ValueType>
bool Set<ValueType>::isEmpty() const {
   return map.isEmpty();
}

template <typename ValueType>
void Set<ValueType>::add(const ValueType & value) {
   map.put(value, true);
}

template <typename ValueType>
void Set<ValueType>::insert(const ValueType & value) {
   map.put(value, true);
}

template <typename ValueType>
void Set<ValueType>::remove(const ValueType & value) {
   map.remove(value);
}

template <typename ValueType>
bool Set<ValueType>::contains(const ValueType & value) const {
   return map.containsKey(value);
}

template <typename ValueType>
void Set<ValueType>::clear() {
   map.clear();
}

template <typename ValueType>
bool Set<ValueType>::isSubsetOf(const Set & set2) const {
   iterator it = begin();
   iterator end = this->end();
   while (it != end) {
      if (!set2.map.containsKey(*it)) return false;
      ++it;
   }
   return true;
}

/*
 * Implementation notes: set operators
 * -----------------------------------
 * The implementations for the set operators use iteration to walk
 * over the elements in one or both sets.
 */

template <typename ValueType>
bool Set<ValueType>::operator==(const Set & set2) const {
   if (size() != set2.map.size()) return false;
   iterator it1 = begin();
   iterator it2 = set2.map.begin();
   iterator end = this->end();
   while (it1 != end) {
      if (map.compareKeys(*it1, *it2) != 0) return false;
      ++it1;
      ++it2;
   }
   return true;
}

template <typename ValueType>
bool Set<ValueType>::operator!=(const Set & set2) const {
   return !(*this == set2);
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator+(const Set & set2) const {
   Set<ValueType> set = *this;
   foreach (ValueType value in set2) {
      set.add(value);
   }
   return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator+(const ValueType & element) const {
   Set<ValueType> set = *this;
   set.add(element);
   return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator*(const Set & set2) const {
   Set<ValueType> set = *this;
   set.clear();
   foreach (ValueType value in *this) {
      if (set2.contains(value)) set.add(value);
   }
   return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator-(const Set & set2) const {
   Set<ValueType> set = *this;
   foreach (ValueType value in set2) {
      set.remove(value);
   }
   return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator-(const ValueType & element) const {
   Set<ValueType> set = *this;
   set.remove(element);
   return set;
}

template <typename ValueType>
Set<ValueType> & Set<ValueType>::operator+=(const Set & set2) {
   foreach (ValueType value in set2) {
      this->add(value);
   }
   return *this;
}

template <typename ValueType>
Set<ValueType> & Set<ValueType>::operator+=(const ValueType & value) {
   this->add(value);
   this->removeFlag = false;
   return *this;
}

template <typename ValueType>
Set<ValueType> & Set<ValueType>::operator*=(const Set & set2) {
   Vector<ValueType> toRemove;
   foreach (ValueType value in *this) {
      if (!set2.map.containsKey(value)) toRemove.add(value);
   }
   foreach (ValueType value in toRemove) {
      this->remove(value);
   }
   return *this;
}

template <typename ValueType>
Set<ValueType> & Set<ValueType>::operator-=(const Set & set2) {
   Vector<ValueType> toRemove;
   foreach (ValueType value in *this) {
      if (set2.map.containsKey(value)) toRemove.add(value);
   }
   foreach (ValueType value in toRemove) {
      this->remove(value);
   }
   return *this;
}

template <typename ValueType>
Set<ValueType> & Set<ValueType>::operator-=(const ValueType & value) {
   this->remove(value);
   this->removeFlag = true;
   return *this;
}

template <typename ValueType>
ValueType Set<ValueType>::first() const {
   if (isEmpty()) error("first: set is empty");
   return *begin();
}

template <typename ValueType>
void Set<ValueType>::mapAll(void (*fn)(ValueType)) const {
   map.mapAll(fn);
}

template <typename ValueType>
void Set<ValueType>::mapAll(void (*fn)(const ValueType &)) const {
   map.mapAll(fn);
}

template <typename ValueType>
template <typename FunctorType>
void Set<ValueType>::mapAll(FunctorType fn) const {
   map.mapAll(fn);
}

template <typename ValueType>
std::ostream & operator<<(std::ostream & stream, const Set<ValueType> & set) {
   stream << "{";
   bool started = false;
   foreach (ValueType value in set) {
      if (started) stream << ", ";
      stream << value;
      started = true;
   }
   stream << "}";
   return stream;
}

template <typename ValueType>
std::istream & operator>>(std::istream & stream, Set<ValueType> & set) {
   ValueType value;
   char ch;
   stream >> ch;
   if (stream.fail() || ch != '{') error("Missing open brace in set");
   while (ch != '}') {
      int parenCount = 0;
      std::string token = "";
      while (true) {
         stream >> ch;
         if (stream.fail()) error("Missing close brace in set");
         if (parenCount == 0 && (ch == ',' || ch == '}')) break;
         if (ch == '(') parenCount++;
         if (parenCount > 0 && ch == ')') parenCount--;
         token += ch;
      }
      std::istringstream iss(token);
      iss >> value;
      if (iss.fail()) error("Illegal value \"" + token + "\" in set");
      set += value;
   }
   return stream;
}

#endif
