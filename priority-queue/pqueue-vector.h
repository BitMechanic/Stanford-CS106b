#ifndef _vector_pqueue_
#define _vector_pqueue_

#include "pqueue.h"
#include <string>
#include "vector.h"



class VectorPQueue : public PQueue {
public:
	VectorPQueue();
	~VectorPQueue();
	
	static VectorPQueue *merge(VectorPQueue *one, VectorPQueue *two);
	
	void enqueue(const std::string& elem);
    std::string extractMin();
    std::string peek() const;
	
private:
    Vector<string> pQueue;
};

#endif