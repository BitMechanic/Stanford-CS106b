/*
 * File: mapimpl.cpp
 * -----------------
 * This file contains the private section of the map.cpp interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _map_h

template <typename KeyType, typename ValueType>
Map<KeyType,ValueType>::Map() {
   root = NULL;
   nodeCount = 0;
   cmpp = new TemplateComparator< less<KeyType> >(less<KeyType>());
}

template <typename KeyType, typename ValueType>
Map<KeyType,ValueType>::~Map() {
   if (cmpp != NULL) delete cmpp;
   deleteTree(root);
}

template <typename KeyType, typename ValueType>
int Map<KeyType,ValueType>::size() const {
   return nodeCount;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType,ValueType>::isEmpty() const {
   return nodeCount == 0;
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::put(const KeyType & key,
                                 const ValueType & value) {
   bool dummy;
   *addNode(root, key, dummy) = value;
}

template <typename KeyType, typename ValueType>
ValueType Map<KeyType,ValueType>::get(const KeyType & key) const {
   ValueType *vp = findNode(root, key);
   if (vp == NULL) return ValueType();
   return *vp;
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::remove(const KeyType & key) {
   removeNode(root, key);
}

template <typename KeyType, typename ValueType>
void Map<KeyType,ValueType>::clear() {
   deleteTree(root);
   root = NULL;
   nodeCount = 0;
}

template <typename KeyType, typename ValueType>
bool Map<KeyType,ValueType>::containsKey(const KeyType & key) const {
   return findNode(root, key) != NULL;
}

template <typename KeyType, typename ValueType>
ValueType & Map<KeyType,ValueType>::operator[](const KeyType & key) {
   bool dummy;
   return *addNode(root, key, dummy);
}

/*
 * Operator: <<
 * Usage: cout << map;
 * -------------------
 * Implements the insertion operator for the Map class.  The key-value
 * pairs are surrounded by curly braces and separated by commas; the
 * key and the value themselves are separated by a colon.
 */

template <typename KeyType, typename ValueType>
std::ostream & operator<<(std::ostream & os,
                          const Map<KeyType,ValueType> & map) {
   os << "{";
   typename Map<KeyType,ValueType>::iterator begin = map.begin();
   typename Map<KeyType,ValueType>::iterator end = map.end();
   typename Map<KeyType,ValueType>::iterator it = begin;
   while (it != end) {
      if (it != begin) os << ", ";
      os << *it << ":" << map.get(*it);
      ++it;
   }
   return os << "}";
}

#endif
