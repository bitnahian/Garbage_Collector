#include "mem_ref.h"
#include <stdio.h>

node_t* head = NULL;
node_t* tail = NULL;

node_t* init_node(void* ptr, size_t count, void* dep)
{
	node_t* new = (node_t*)malloc(sizeof(node_t));
	new->ptr = ptr;
	new->count = count; // Check the chat bau. 
	new->next = NULL;
	new->prev = NULL;
	new->parent = (node_t*) dep;
	return new;
}

void insertAtTail(void* ptr, size_t count, void* dep)
{
	node_t* new = init_node(ptr, count, dep);
	if(head == NULL && tail == NULL)
	{
		head = new;
		tail = new;
		return;
	}
	tail->next = new;
	new->prev = tail;
	tail = new;
}

void deleteNode(node_t *node)
{
	if(head->next == NULL) // If there is only one node
	{	
		free(head->ptr);
		free(head);
		return;
    }
	if(node == head) // If the node is the head
	{
		node->next->prev = NULL;
		head = node->next;
	}
	else if(node == tail) // If the node is the tail
	{
		node->prev->next = NULL;
		tail = node->prev;

	}
	else
	{
		node_t* temp = node;
		temp->prev->next = node->next;
		temp->next->prev = node->prev;
	}
	free(node->ptr);
	free(node);
}

void* new_ref(size_t size, void* dep) {
	
	void* ptr = malloc(size);
	insertAtTail(ptr, 1, dep);
	return ptr;
}

void* assign_ref(void* ref) {
	node_t* temp = head;
	while(temp->next !=NULL)
	{
		if(temp->ptr == ref)
		{
			temp->count++;
			break;
		}
		temp = temp->next;
	}
	return temp->ptr;
}

void* del_ref(void* ref) {
	node_t* temp = head;
	while(temp->next != NULL)
	{
		if(temp->ptr == ref)
			break;
		temp=temp->next;
	}
	// We have the node we want to delete. Might have to perform recursive stuff.
	// First check if count = 1
	if(temp->count > 1)
	{
		temp->count--;
		return NULL;
	}
	// Delete all children as well
	node_t* child = head;
	while(child != NULL)
	{
		if(child->parent == temp)
			del_ref(child->ptr);
		child = child->next;
	}
	deleteNode(temp);
	return NULL;
}


