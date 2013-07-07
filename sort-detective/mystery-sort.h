/**
 * File: mystery-sort.h
 * --------------------
 * This interface exports a set of poorly named sorting routines.
 */

#ifndef _mystery_sort_
#define _mystery_sort_

#include "vector.h"

/**
 * Function: mysterySort1, mysterySort2, etc.
 * Usage:  mysterySort1(scores);
 * -----------------------------
 * Each of these functions will sort a vector of integers into ascending order.
 * Each uses a different sorting algoritm, and therein lies the mystery!
 *
 * The optional second argument is a value that limits the sort to a given
 * amount of processing time.  The maxSecs argument is expressed in seconds.
 * The function will return after that much time has elapsed (approximately),
 * even if the sorting hasn't been finished. By choosing an appropriate stop,
 * you can examine the data mid-sort, which allows you to look for patterns in
 * how the data is being rearranged. The default argument sets maxSecs to -1,
 * which indicates the sort should be run to completion.  Note that maxSecs can
 * be specified as a fractional value (e.g. .001) which is handy because a lot
 * of processing can occur in even just 1 whole second.
 */

void mysterySort1(Vector<int> &nums, double maxSecs = -1);
void mysterySort2(Vector<int> &nums, double maxSecs = -1);
void mysterySort3(Vector<int> &nums, double maxSecs = -1);
void mysterySort4(Vector<int> &nums, double maxSecs = -1);
void mysterySort5(Vector<int> &nums, double maxSecs = -1);

#endif