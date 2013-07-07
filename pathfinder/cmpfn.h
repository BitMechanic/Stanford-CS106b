//
//  cmpfn.h
//  pathfinder
//
//  Created by Robbie on 08/06/2013.
//
//

#ifndef pathfinder_cmpfn_h
#define pathfinder_cmpfn_h

#include "path.h"

/*
 * Function: operatorCmp
 * Usage: int sign = operatorCmp(v1, v2);
 * --------------------------------------
 * This template function is a generic function that compares two values
 * using the built-in == and < operators.  It is supplied as a convenience
 * for those situations where a comparison function is required, and the
 * type has a built-in ordering that you would like to use.
 */


template <typename Type>
int operatorCmp(Type v1, Type v2) {
    if (v1 == v2) return 0;
    if (v1 < v2) return -1;
    return 1;
}

int arcCmp(Arc *one, Arc *two) {// Arc comparator
    if (one->cost == two->cost) return 0;
    if (one->cost < two->cost) return -1;
    return 1;
}

int pathCmp(Path one, Path two) {// Path comparator for dijkstra
    if (one.pathcost == two.pathcost) return 0;
    if (one.pathcost < two.pathcost) return -1;
    return 1;
}

#endif
