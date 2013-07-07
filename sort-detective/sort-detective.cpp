/**
 * File: sort-detective.cpp
 * ------------------------
 * This provides provides nothing beyond a shell of a main
 * function that you should use to discern what algorithms
 * are backing each of mystersort[1-5].
 */

#include <string>
#include "strlib.h"
#include "simpio.h"
#include <iostream>
#include <cassert>
#include "console.h"
#include "vector.h"
#include "random.h"
#include "mystery-sort.h"
#include "set.h"



using namespace std;

template <typename Type>
void mySort(Vector<Type>& t, int start, int finish);
template <typename Type>
int Partition(Vector<Type>& t, int start, int finish);
static void seed(Vector<int>& v, int size);
static void reverseSeed(Vector<int>& v, int size);
static void shuffle(Vector<int>& v);
static bool operator==(const Vector<int>& one, const Vector<int>& two);
static const double kNoTimeLimit = -1.0;
static const int kTestVectorSize = 10000;
static void testSortRoutines();


int main() {
    testSortRoutines();
    return 0;
}

static void seed(Vector<int>& v, int size) {
    v.clear();
    for (int n = 1; n <= size; n++) {
        v += n;
    }
}

static void reverseSeed(Vector<int>& v, int size) {
    v.clear();
    int count = size;
    for (int n = 0; n < size; n++) {
        v += count;
        count--;
    }
}

static void shuffle(Vector<int>& v) {
    for (int lh = 0; lh < v.size(); lh++) {
        int rh = randomInteger(lh, v.size() - 1);
        swap(v[lh], v[rh]);
    }
}

static bool operator==(const Vector<int>& one, const Vector<int>& two) {
    if (one.size() != two.size()) return false;
    for (int i = 0; i < one.size(); i++) {
        if (one.get(i) != two.get(i)) {
            return false;
        }
    }
    
    return true;
}

static void testSortRoutines() {
    Vector<void (*)(Vector<int>&, double)> sorts;
    sorts += mysterySort1, mysterySort2, mysterySort3, mysterySort4, mysterySort5;
    cout << "Times for random sort." << endl << endl;
    for (int i = 0; i < sorts.size(); i++) {
        Vector<int> s;
        seed(s, kTestVectorSize);
        Vector<int> t = s;
        shuffle(t);
        double start = double(clock());
        sorts[i](t, kNoTimeLimit);
        double finish = double(clock());
        double elapsed = finish - start;
        string elapsedtime = integerToString(elapsed);
        if (s == t) {
            cout << "    mysterySort" << (i + 1) << " works.  Elapsed time= " + elapsedtime << endl;
        } else {
            cout << "    mysterySort" << (i + 1) << " doesn't work." << endl;
        }
    }
    cout << endl;
    cout << "Times for random sort, for mySort." << endl << endl;
    Vector<int> s;
    seed(s, kTestVectorSize);
    Vector<int> t = s;
    shuffle(t);
    double start = double(clock());
    mySort(t, 0, kTestVectorSize - 1);
    double finish = double(clock());
    double elapsed = finish - start;
    string elapsedtime = integerToString(elapsed);
    if (s == t) {
        cout << "    mySort works.  Elapsed time= " + elapsedtime << endl;
    } else {
        cout << "    mySort doesn't work." << endl;
    }

    cout << endl;
    cout << "Times to sort fully sorted vector, for mySort." << endl << endl;
    seed(s, kTestVectorSize);
    t = s;
    start = double(clock());
    mySort(t, 0, kTestVectorSize - 1);
    finish = double(clock());
    elapsed = finish - start;
    elapsedtime = integerToString(elapsed);
    if (s == t) {
        cout << "    mySort works.  Elapsed time= " + elapsedtime << endl;
    } else {
        cout << "    mySort doesn't work." << endl;
    }
    
    cout << endl;
    cout << "Times to sort reverse sorted vector, for mySort." << endl << endl;
    seed(s, kTestVectorSize);
    t = s;
    reverseSeed(s, kTestVectorSize);
    start = double(clock());
    mySort(s, 0, kTestVectorSize - 1);
    finish = double(clock());
    elapsed = finish - start;
    elapsedtime = integerToString(elapsed);
    if (s == t) {
        cout << "    mySort works.  Elapsed time= " + elapsedtime << endl;
    } else {
        cout << "    mySort doesn't work." << endl;
    }

    
    cout << endl;
    cout << "Times to sort fully sorted vector." << endl << endl;
    for (int i = 0; i < sorts.size(); i++) {
        Vector<int> s;
        seed(s, kTestVectorSize);
        Vector<int> t = s;
        double start = double(clock());
        sorts[i](t, kNoTimeLimit);
        double finish = double(clock());
        double elapsed = finish - start;
        string elapsedtime = integerToString(elapsed);
        if (s == t) {
            cout << "    mysterySort" << (i + 1) << " works.  Elapsed time= " + elapsedtime << endl;
        } else {
            cout << "    mysterySort" << (i + 1) << " doesn't work." << endl;
        }
    }






    cout << endl;
    cout << "Times to sort a reverse sorted vector." << endl << endl;
    for (int i = 0; i < sorts.size(); i++) {
        Vector<int> s;
        seed(s, kTestVectorSize);
        Vector<int> t = s;
        reverseSeed(s, kTestVectorSize);
        double start = double(clock());
        sorts[i](s, kNoTimeLimit);
        double finish = double(clock());
        double elapsed = finish - start;
        string elapsedtime = integerToString(elapsed);
        if (s == t) {
            cout << "    mysterySort" << (i + 1) << " works.  Elapsed time= " + elapsedtime << endl;
        } else {
            cout << "    mysterySort" << (i + 1) << " doesn't work." << endl;
        }
    }



}

template <typename Type>
void mySort(Vector<Type>& t, int start, int finish) {
    if (start >= finish) return;
    int boundary = Partition(t, start, finish);
    mySort(t, start, boundary - 1);
    mySort(t, boundary + 1, finish);
}

template <typename Type>
int Partition(Vector<Type>& t, int start, int finish) {
    int randompoint = randomInteger(start, finish);
    Type pivot = t[randompoint];
    Type startvalue = t[start];
    t[start] = pivot;
    t[randompoint] = startvalue;
    int count = start + 1;
    int rh = finish;
    while (true) {
        while (count < rh && t[rh] >= pivot) rh--;
        while (count < rh && t[count] < pivot) count++;
        if (count == rh) break;
        int temp = t[count];
        t[count] = t[rh];
        t[rh] = temp;
    }
    if (t[count] >= pivot) return start;
    t[start] = t[count];
    t[count] = pivot;
    return count;
}

