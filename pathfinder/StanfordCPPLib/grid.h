/*
 * File: grid.h
 * ------------
 * This interface exports the <code>Grid</code> template class, which
 * provides a convenient abstraction for representing two-dimensional
 * arrays.
 */

#ifndef _grid_h
#define _grid_h

#include "foreach.h"
#include "strlib.h"

/*
 * Class: Grid<ValueType>
 * ----------------------
 * The <code>Grid</code> class stores an indexed, two-dimensional
 * array.  The following function, for example, creates an identity
 * matrix of size <code>n</code>, in which the elements are 1.0
 * along the main diagonal and 0.0 everywhere else:
 *
 *<pre>
 *    Grid&lt;double&gt; createIdentityMatrix(int n) {
 *       Grid&lt;double&gt; matrix(n, n);
 *       for (int i = 0; i &lt; n; i++) {
 *          matrix[i][i] = 1.0;
 *       }
 *       return matrix;
 *    }
 *</pre>
 */

template <typename ValueType>
class Grid {

public:

/* Forward reference */
   class GridRow;

/*
 * Constructor: Grid
 * Usage: Grid<ValueType> grid;
 *        Grid<ValueType> grid(nRows, nCols);
 * ------------------------------------------
 * Initializes a new grid.  The second form of the constructor is
 * more common and creates a grid with the specified number of rows
 * and columns.  Each element of the grid is initialized to the
 * default value for the type.  The default constructor creates an
 * empty grid for which the client must call <code>resize</code> to
 * set the dimensions.
 */

   Grid();
   Grid(int nRows, int nCols);

/*
 * Destructor: ~Grid
 * -----------------
 * Frees any heap storage associated with this grid.
 */

   ~Grid();

/*
 * Method: numRows
 * Usage: int nRows = grid.numRows();
 * ----------------------------------
 * Returns the number of rows in the grid.
 */

   int numRows() const;

/*
 * Method: numCols
 * Usage: int nCols = grid.numCols();
 * ----------------------------------
 * Returns the number of columns in the grid.
 */

   int numCols() const;

/*
 * Method: resize
 * Usage: grid.resize(nRows, nCols);
 * ---------------------------------
 * Reinitializes the grid to have the specified number of rows
 * and columns.  Any previous grid contents are discarded.
 */

   void resize(int nRows, int nCols);

/*
 * Method: inBounds
 * Usage: if (grid.inBounds(row, col)) . . .
 * -----------------------------------------
 * Returns <code>true</code> if the specified row and column position
 * is inside the bounds of the grid.
 */

   bool inBounds(int row, int col) const;

/*
 * Method: get
 * Usage: ValueType value = grid.get(row, col);
 * --------------------------------------------
 * Returns the element at the specified <code>row</code>/<code>col</code>
 * position in this grid.  This method signals an error if the
 * <code>row</code> and <code>col</code> arguments are outside
 * the grid boundaries.
 */

   ValueType get(int row, int col) const;

/*
 * Method: set
 * Usage: grid.set(row, col, value);
 * ---------------------------------
 * Replaces the element at the specified <code>row</code>/<code>col</code>
 * location in this grid with a new value.  This method signals an error
 * if the <code>row</code> and <code>col</code> arguments are outside
 * the grid boundaries.
 */

   void set(int row, int col, ValueType value);

/*
 * Operator: []
 * Usage:  grid[row][col]
 * ----------------------
 * Overloads <code>[]</code> to select elements from this grid.
 * This extension enables the use of traditional array notation to
 * get or set individual elements.  This method signals an error if
 * the <code>row</code> and <code>col</code> arguments are outside
 * the grid boundaries.
 */

   GridRow operator[](int row);
   const GridRow operator[](int row) const;

/*
 * Additional Grid operations
 * --------------------------
 * In addition to the methods listed in this interface, the Grid
 * class supports the following operations:
 *
 *   - Stream insertion using the &lt;&lt; operator
 *   - Deep copying for the copy constructor and assignment operator
 *   - Iteration using the range-based for statement, standard STL
 *     iterators, and the mapping function mapAll
 *
 * The iteration forms process the Grid in row-major order.
 */

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

/*
 * Implementation notes: Grid data structure
 * -----------------------------------------
 * The Grid is internally managed as a dynamic array of elements.
 * The array itself is one-dimensional, the logical separation into
 * rows and columns is done by arithmetic computation.  The layout
 * is in row-major order, which is to say that the entire first row
 * is laid out contiguously, followed by the entire second row,
 * and so on.
 */

/* Instance variables */

   ValueType *elements;  /* A dynamic array of the elements   */
   int nRows;            /* The number of rows in the grid    */
   int nCols;            /* The number of columns in the grid */

/* Private method prototypes */

   void checkRange(int row, int col);

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
 * deep copy, making it possible to pass/return grids by value
 * and assign from one grid to another. The entire contents of
 * the grid, including all elements, are copied. Each grid
 * element is copied from the original grid to the copy using
 * assignment (operator=). Making copies is generally avoided
 * because of the expense and thus, grids are typically passed
 * by reference, however, when a copy is needed, these operations
 * are supported.
 */

   void copyInternalData(const Grid & grid) {
      int n = grid.nRows * grid.nCols;
      elements = new ValueType[n];
      for (int i = 0; i < n; i++) {
         elements[i] = grid.elements[i];
      }
      nRows = grid.nRows;
      nCols = grid.nCols;
   }

public:

   Grid & operator=(const Grid & rhs) {
      if (this != &rhs) {
         delete[] elements;
         copyInternalData(rhs);
      }
      return *this;
   }

   Grid(const Grid & rhs) {
      copyInternalData(rhs);
   }

/*
 * Method: mapAll
 * Usage: grid.mapAll(fn);
 * -----------------------
 * Calls the specified function on each element of the grid.  The
 * elements are processed in <i>row-major order,</i> in which all
 * the elements of row 0 are processed, followed by the elements
 * in row 1, and so on.
 */

   void mapAll(void (*fn)(ValueType value)) const {
      for (int i = 0; i < nRows * nCols; i++) {
         fn(elements[i]);
      }
   }

   void mapAll(void (*fn)(const ValueType & value)) const {
      for (int i = 0; i < nRows * nCols; i++) {
         fn(elements[i]);
      }
   }

   template <typename FunctorType>
   void mapAll(FunctorType fn) const {
      for (int i = 0; i < nRows * nCols; i++) {
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

   class iterator : public std::iterator<std::input_iterator_tag, ValueType> {

   public:

      iterator(const Grid *gp, int index) {
         this->gp = gp;
         this->index = index;
      }

      iterator(const iterator & it) {
         this->gp = it.gp;
         this->index = it.index;
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

      bool operator==(const iterator & rhs) {
         return gp == rhs.gp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      ValueType & operator*() {
         return gp->elements[index];
      }

      ValueType *operator->() {
         return &gp->elements[index];
      }

   private:
      const Grid *gp;
      int index;
   };

   iterator begin() const {
      return iterator(this, 0);
   }

   iterator end() const {
      return iterator(this, nRows * nCols);
   }

/*
 * Class: Grid<ValType>::GridRow
 * -----------------------------
 * This section of the code defines a nested class within the Grid template
 * that makes it possible to use traditional subscripting on Grid values.
 */

   class GridRow {
   public:
      GridRow() {
         /* Empty */
      }

      ValueType & operator[](int col) {
         extern void error(std::string msg);
         if (!gp->inBounds(row, col)) {
            error("Grid index values out of range");
         }
         return gp->elements[(row * gp->nCols) + col];
      }

      ValueType operator[](int col) const {
         extern void error(std::string msg);
         if (!gp->inBounds(row, col)) {
            error("Grid index values out of range");
         }
         return gp->elements[(row * gp->nCols) + col];
      }

   private:
      GridRow(Grid *gridRef, int index) {
         gp = gridRef;
         row = index;
      }

      Grid *gp;
      int row;
      friend class Grid;
   };
   friend class GridRow;

};

extern void error(std::string msg);

template <typename ValueType>
Grid<ValueType>::Grid() {
   elements = NULL;
   nRows = 0;
   nCols = 0;
}

template <typename ValueType>
Grid<ValueType>::Grid(int nRows, int nCols) {
   elements = NULL;
   resize(nRows, nCols);
}

template <typename ValueType>
Grid<ValueType>::~Grid() {
   if (elements != NULL) delete[] elements;
}

template <typename ValueType>
int Grid<ValueType>::numRows() const {
   return nRows;
}

template <typename ValueType>
int Grid<ValueType>::numCols() const {
   return nCols;
}

template <typename ValueType>
void Grid<ValueType>::resize(int nRows, int nCols) {
   if (nRows < 0 || nCols < 0) {
      error("Attempt to resize grid to invalid size ("
            + integerToString(nRows) + ", "
            + integerToString(nCols) + ")");
   }
   if (elements != NULL) delete[] elements;
   this->nRows = nRows;
   this->nCols = nCols;
   elements = new ValueType[nRows * nCols];
   ValueType value = ValueType();
   for (int i = 0; i < nRows * nCols; i++) {
      elements[i] = value;
   }
}

template <typename ValueType>
bool Grid<ValueType>::inBounds(int row, int col) const {
   return row >= 0 && col >= 0 && row < nRows && col < nCols;
}

template <typename ValueType>
ValueType Grid<ValueType>::get(int row, int col) const {
   if (!inBounds(row, col)) error("get: Grid indices out of bounds");
   return elements[(row * nCols) + col];
}

template <typename ValueType>
void Grid<ValueType>::set(int row, int col, ValueType value) {
   if (!inBounds(row, col)) error("set: Grid indices out of bounds");
   elements[(row * nCols) + col] = value;
}

template <typename ValueType>
typename Grid<ValueType>::GridRow Grid<ValueType>::operator[](int row) {
   return GridRow(this, row);
}

template <typename ValueType>
const typename Grid<ValueType>::GridRow
               Grid<ValueType>::operator[](int row) const {
   return GridRow(this, row);
}

/*
 * Operator: <<
 * Usage: cout << grid;
 * --------------------
 * Implements the insertion operator for the Grid class.  The output
 * appears as a nested vector on a single line.
 */

template <typename ValueType>
std::ostream & operator<<(ostream & os, const Grid<ValueType> & grid) {
   os << "{";
   int nRows = grid.numRows();
   int nCols = grid.numCols();
   for (int i = 0; i < nRows; i++) {
      if (i > 0) os << ", ";
      os << "{";
      for (int j = 0; j < nCols; j++) {
         if (j > 0) os << ", ";
         os << grid.get(i, j);
      }
      os << "}";
   }
   return os << "}";
}

#endif
