/**
 * File: dominosa-types.h
 * ----------------------
 * Exports a simple coord struct to bundle a row and
 * column into a single package.  We also ensure that
 * < works with coords, so they can be stored in Sets
 * as as the keys in Maps.
 *
 * The assumption is that the upper left corner of the
 * board, as with the graphics window, is the origin (0, 0).
 */

#ifndef _dominosa_types_
#define _dominosa_types_

struct coord {
    int row;
    int col;
};

/**
 * Function: operator<
 * Usage: if (c1 < c2) { ...
 * -------------------
 * Returns true if and only if the row within the first cell is less than the
 * row within the second, or if the two rows are equal and the first column
 * is less than the second.
 */

#endif
