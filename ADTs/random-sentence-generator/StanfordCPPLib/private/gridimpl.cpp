/*
 * File: gridimpl.cpp
 * ------------------
 * This file contains the implementation of the grid.h interface.
 * Because of the way C++ compiles templates, this code must be
 * available to the compiler when it reads the header file.
 */

#ifdef _grid_h

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
