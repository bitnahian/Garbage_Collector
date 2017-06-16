#include <stdio.h>

#include "mem_ref.h"
//File to run and test your code

struct player {
    char* name;
    int rank;
};

int main(int argc, char** argv)
{
	struct player* p = new_ref(sizeof(struct player), NULL);
    p->name = new_ref(sizeof(char)*20, p);
    
    //Do things
    
    //Extension:
    char* str = assign_ref(p->name);
    
    //Normal thing
    p = del_ref(p); //removes p gets deallocated, str decrements
    str = del_ref(str); //removes str
}
