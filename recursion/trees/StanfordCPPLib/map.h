/*
 * File: map.h
 * -----------
 * This interface exports the template class <code>Map</code>, which
 * maintains a collection of <i>key</i>-<i>value</i> pairs.
 */

#ifndef _map_h
#define _map_h

#include <cstdlib>
#include "error.h"
#include "foreach.h"
#include "stack.h"

/*
 * Class: Map<KeyType,ValueType>
 * -----------------------------
 * The <code>Map</code> class maintains an association between
 * keys and values.  The types used for keys and values are
 * specified using templates, which makes it possible to use
 * this structure with any data type.
 */

template <typename KeyType, typename ValueType>
class Map {

public:

/*
 * Constructor: Map
 * Usage: Map<KeyType,ValueType> map;
 * ----------------------------------
 * Initializes a new empty map that associates keys and values of the
 * specified types.
 */

   Map();

/*
 * Destructor: ~Map
 * ----------------
 * Frees any heap storage associated with this map.
 */

   ~Map();

/*
 * Method: size
 * Usage: int nEntries = map.size();
 * ---------------------------------
 * Returns the number of entries in this map.
 */

   int size() const;

/*
 * Method: isEmpty
 * Usage: if (map.isEmpty()) . . .
 * -------------------------------
 * Returns <code>true</code> if this map contains no entries.
 */

   bool isEmpty() const;

/*
 * Method: put
 * Usage: map.put(key, value);
 * ---------------------------
 * Associates <code>key</code> with <code>value</code> in this map.
 * Any previous value associated with <code>key</code> is replaced
 * by the new value.
 */

   void put(const KeyType & key, const ValueType & value);

/*
 * Method: get
 * Usage: ValueType value = map.get(key);
 * --------------------------------------
 * Returns the value associated with <code>key</code> in this map.
 * If <code>key</code> is not found, <code>get</code> returns the
 * default value for <code>ValueType</code>.
 */

   ValueType get(const KeyType & key) const;

/*
 * Method: containsKey
 * Usage: if (map.containsKey(key)) . . .
 * --------------------------------------
 * Returns <code>true</code> if there is an entry for <code>key</code>
 * in this map.
 */

   bool containsKey(const KeyType & key) const;

/*
 * Method: remove
 * Usage: map.remove(key);
 * -----------------------
 * Removes any entry for <code>key</code> from this map.
 */

   void remove(const KeyType & key);

/*
 * Method: clear
 * Usage: map.clear();
 * -------------------
 * Removes all entries from this map.
 */

   void clear();

/*
 * Operator: []
 * Usage: map[key]
 * ---------------
 * Selects the value associated with <code>key</code>.  This syntax
 * makes it easy to think of a map as an "associative array"
 * indexed by the key type.  If <code>key</code> is already present
 * in the map, this function returns a reference to its associated
 * value.  If key is not present in the map, a new entry is created
 * whose value is set to the default for the value type.
 */

   ValueType & operator[](const KeyType & key);

/*
 * Additional Map operations
 * -------------------------
 * In addition to the methods listed in this interface, the Map
 * class supports the following operations:
 *
 *   - Stream insertion using the &lt;&lt; operator
 *   - Deep copying for the copy constructor and assignment operator
 *   - Iteration using the range-based for statement, standard STL
 *     iterators, and the mapping function mapAll
 *
 * All iteration is guaranteed to proceed in the order established by
 * the comparison function passed to the constructor, which ordinarily
 * matches the order of the key type.
 */

#include "private/mappriv.h"

};

#include "private/mapimpl.cpp"

#endif
