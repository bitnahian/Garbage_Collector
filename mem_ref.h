#ifndef MEM_REF_H
#define MEM_REF_H

#include <stdlib.h>
typedef struct node_t node_t;

struct node_t{
	void* ptr;
	size_t count;
	node_t* next;
	node_t* prev;
	node_t* parent;
};


void* new_ref(size_t size, void* dep);
void* assign_ref(void* ref);
void* del_ref(void* ref);


#endif
