#include "pqueue-binomial-heap.h"
#include <cmath>
#include <bitset>
using namespace std;

BinomialHeapPQueue::BinomialHeapPQueue() {
    carry = NULL;
}

BinomialHeapPQueue::~BinomialHeapPQueue() {
}

string BinomialHeapPQueue::peek() const {
    int key = findKey();
    node *keynode = heap.get(key);
    string nextword = keynode->word;
	return nextword;
}

string BinomialHeapPQueue::extractMin() {
	int key = findKey();
    node *keynode = heap[key];
    string nextword = keynode->word;
    deleteNode(key);
	return nextword;
}

void BinomialHeapPQueue::enqueue(const string& elem) {
    node *newnode = new node;
    newnode->word = elem;
    if (heap.size() == 0) {
        heap.push_back(NULL);
    }
    newheap.push_back(newnode);
    mergeHeaps();
    logSize++;
}

int BinomialHeapPQueue::findKey() const {
    int minimum = 0;
    string minstring = "zzzzzzzzz";
    for (int i = 0; i < heap.size(); i++) {
        node *check = heap.get(i);
        if (check != NULL) {
        string checkstring = check->word;
        if (checkstring < minstring) {
            minimum = i;
            }
        }
    }
    return minimum;
}

void BinomialHeapPQueue::deleteNode(int key) {
    node *dnode = heap[key];
    newheap = dnode->children;
    dnode = NULL;
    logSize--;
    mergeHeaps();
}

void BinomialHeapPQueue::mergeHeaps() {
    int i = 0;
    
    while (i < heap.size() && i < newheap.size()) {
        node *currentp = heap[i];// node from heap
        node *currentq = newheap[i];// node from the newheap being merged into heap
        
        if (currentp == NULL && currentq == NULL && carry == NULL) {
            heap[i] = NULL;
            i++;
        }
        else if (currentp != NULL && currentq != NULL && carry != NULL) {
            heap[i] = currentp;
            carry = mergeTree(carry, currentq);
                if (i >= heap.size() - 1) {// extend vector/s if reaching the end and there's still something being carried.
                    heap.add(NULL);
            }
                if (i >= newheap.size() -1) {// better to do it this way than make one vector same size as the other- then enqueue gets expensive
                    newheap.add(NULL);
            }
            i++;
        }
        else if (currentp == NULL && currentq == NULL && carry != NULL) {
            heap[i] = carry;
            //deleteTree(carry); //comment out deleteTree because it's not working right now.
            carry = NULL;
            i++;
        }
        else if (currentp != NULL && currentq != NULL && carry == NULL) {
            carry = mergeTree(currentp, currentq);
            heap[i] = NULL;
                if (i >= heap.size() - 1) {
                    heap.add(NULL);
            }
                if (i >= newheap.size() -1) {
                    newheap.add(NULL);
            }
            i++;
        }
        else if (currentp == NULL && currentq != NULL && carry != NULL) {
            carry = mergeTree(currentq, carry);
            heap[i] = NULL;
                if (i >= heap.size() - 1) {
                   heap.add(NULL);
            }
                if (i >= newheap.size() -1) {
                   newheap.add(NULL);
            }
            i++;
        }
        else if (currentp != NULL && currentq == NULL && carry != NULL) {
            carry = mergeTree(currentp, carry);
            heap[i] = NULL;
                if (i >= heap.size() - 1) {
                    heap.add(NULL);
            }
                if (i >= newheap.size() -1) {
                    newheap.add(NULL);
            }
            i++;
        }
        else if (currentp != NULL && currentq == NULL && carry == NULL) {
            i++;
        }
        else if (currentp == NULL && currentq != NULL && carry == NULL) {
            heap[i] = currentq;
            i++;
        }
        
    }
    newheap.clear();
    
}

void BinomialHeapPQueue::deleteTree(node * &tree) {
    if (tree == NULL) return;
    
    
    int size = tree->children.size();
    if (size > 0) {
    for (int i = 0; i < size; i++) {
        node *nexttree = tree->children[i];
        if (i == size - 1) {
            tree->children.clear();
        }
        deleteTree(nexttree);
        }
    }
    delete tree;
}

void BinomialHeapPQueue::deleteVector(Vector<node *> &vec) {
    int vecsize = vec.size();
    for (int i = 0; i < vecsize; i++) {
        if (vec.get(i) != NULL) {
            node *startnode = vec.get(i);
            deleteTree(startnode);
        }
    }
    vec.clear();
}


BinomialHeapPQueue *BinomialHeapPQueue::merge(BinomialHeapPQueue *one, BinomialHeapPQueue *two) {
    
	return new BinomialHeapPQueue();
}


typename BinomialHeapPQueue::node *BinomialHeapPQueue::mergeTree(node * &currentp, node * &currentq) {
    string root1 = currentp->word;
    string root2 = currentq->word;
        if (root1 <= root2) {
            return addSubTree(currentp, currentq);
    }
        else {
            return addSubTree(currentq, currentp);
    }
}

typename BinomialHeapPQueue::node *BinomialHeapPQueue::addSubTree(node * &root, node * &add) {
    root->children.add(add);
    return root;
}