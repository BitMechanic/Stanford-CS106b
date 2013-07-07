/**
 * File: pqueue-test.cpp
 * ---------------------
 * Framework in place to exercise all of the different
 * implemenations of the PQueue subclasses.
 */

#include <iostream>
#include "pqueue.h"
#include <bitset>
#include "lexicon.h"
#include "map.h"
#include "random.h"
#include "console.h"
#define PR(x) cout << #x " = " << x << "\n";
using namespace std;

template <typename Iterable>
static PQueue *buildPQueue(PQueue::PQueueType pqtype, Iterable iter, int size) {
	PQueue *pq = PQueue::createPQueue(pqtype);
	int count = 0;
	foreach (string key in iter) {
		pq->enqueue(key);
        
		count++;
        //string s = bitset< 32 > (count).to_string();
        //PR(s);
		if (count == size) break;
	}
	
	cout << "+ Inserted " << pq->size() << " words." << endl;
	return pq;
}

static void extractElements(PQueue::PQueueType pqtype, PQueue *pq) {
	string leastSoFar;
	cout << "+ Extracting all elements, and confirming they come in alphabetical order." << endl;
	cout << "     [You'll see a dot for every 1000 extracted.]" << endl << "     ";

	int count = 0;
	int numExtractionsExpected = pq->size();
	while (!pq->isEmpty()) {
		string next = pq->extractMin();
		if (next < leastSoFar) error("Priority Queue is returning elements in the wrong order.");
		leastSoFar = next;
		count++;
		if (count % 1000 == 0) {
			cout << ".";
			cout.flush();
			if (count % 40000 == 0) {
				cout << endl << "     ";
				cout.flush();
			}
		}
	}
	
	cout << endl;
	if (count != numExtractionsExpected) {
		ostringstream os;
		os << "Priority queue of type " << PQueue::typeToName(pqtype) << " had " << numExtractionsExpected <<
			  " elements, but we only extracted " << count << " of them." << endl;
		error(os.str());
	}
	cout << "+ Properly extracted all " << count << " elements from the priority queue." << endl;
}

static void sortedTest(PQueue::PQueueType pqtype, Lexicon& english, int size) {
	PQueue *pq = buildPQueue(pqtype, english, size);
	extractElements(pqtype, pq);
	delete pq;
	cout << "+ SortedTest seems to work well with the " << PQueue::typeToName(pqtype) << ", provided destructor works properly." << endl;
}

static void scrambleTest(PQueue::PQueueType pqtype, Lexicon& english, int size) {
	Map<string, bool> map;
	foreach (string word in english) map[word] = true;
	PQueue *pq = buildPQueue(pqtype, map, size);
	extractElements(pqtype, pq);
	delete pq;
	cout << "+ ScrambledTest seems to work well with the " << PQueue::typeToName(pqtype) << ", provided destructor works properly." << endl;
}

static string createRandomString() {
	string s(16, '-');
	for (int i = 0; i < s.size(); i++) 
		s[i] = randomInteger('a', 'z');
	return s;
}

static void randomizedTest(PQueue::PQueueType pqtype, int size) {
	Vector<string> randomStrings;
	size = min(size, 100000);
	for (int i = 0; i < size; i++) randomStrings.add(createRandomString());
	PQueue *pq = buildPQueue(pqtype, randomStrings, size);
	extractElements(pqtype, pq);
	delete pq;
	cout << "+ RandomizedTest seems to work well with the " << PQueue::typeToName(pqtype)
         << ", provided destructor works properly." << endl;
}

static void mergeTest(PQueue::PQueueType pqtype, Lexicon& english, int size) {
	Map<string, bool> map;
	foreach (string word in english) map[word] = true;
	cout << "+ Constructing two priority queues to exercise merge." << endl;
	PQueue *pq1 = buildPQueue(pqtype, map, size);
	PQueue *pq2 = buildPQueue(pqtype, map, size);
	int size1 = pq1->size();
	int size2 = pq2->size();
	PQueue *pq = PQueue::merge(pq1, pq2);

	if (size1 + size2 != pq->size()) {
		error("Priority Queue merge clearly failed, because size of "
              "merge doesn't equal the sum of the two original sizes.");
	}
		
	while (!pq->isEmpty()) {
		string one = pq->extractMin();
		string two = pq->extractMin();
		//if (one != two) error("Merge of two identical priority queues "
                              //"should have two copies of all entries.");
		map.remove(one);
	}
	
	delete pq;
	cout << "+ MergeTest seems to work well with the " << PQueue::typeToName(pqtype) << ", provided destructor works properly." << endl;
}

static const struct {
	PQueue::PQueueType type;
	int reasonableTestSize;
} testParameters[] = {
    { PQueue::UnsortedVector, 10000},
    { PQueue::LinkedList, 10000},
    { PQueue::Heap, INT_MAX},
    { PQueue::BinomialHeap, INT_MAX}
};

int main() {
    setConsoleSize(1000, 400);
    setConsoleFont("Courier-BOLD-16");
	Lexicon english("EnglishWords.dat");
	for (int i = 0; i < sizeof(testParameters)/sizeof(*testParameters); i++) {
		cout << "Exercising the " << PQueue::typeToName(testParameters[i].type) << endl;
		cout << "---------------" << string(PQueue::typeToName(testParameters[i].type).size(), '-') << endl;
		sortedTest(testParameters[i].type, english, testParameters[i].reasonableTestSize);
		scrambleTest(testParameters[i].type, english, testParameters[i].reasonableTestSize);
		randomizedTest(testParameters[i].type, testParameters[i].reasonableTestSize);
		mergeTest(testParameters[i].type, english, testParameters[i].reasonableTestSize / 10);
		cout << endl;
	}
	
	return 0;
}
