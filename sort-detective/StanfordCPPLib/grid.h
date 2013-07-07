/*
 * File: grid.h
 * ------------
 * This interface exports the <code>Grid</code> template class, which
 * provides a convenient abstraction for representing two-dimensional
 * arrays.
 */

#ifndef _grid_h
#define _grid_h

#include "error.h"
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

#include "private/gridpriv.h"

};

#include "private/gridimpl.cpp"

#endif
