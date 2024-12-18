#ifndef GC_H
#define GC_H

#include <stddef.h>

/*
This comment acts as a way for me to remember what I did when implementing a GC.
Implementation inspired by: https://craftinginterpreters.com/garbage-collection.html

"Reachability"
- All roots are reachable
- Any object referred to from a reachable object is itself reachable.

"Mark and Sweep Garbage Collection"

Marking:
We start with the roots and traverse or trace through all of the objects those roots refer to.
This is a classic graph traversal of all of the reachable objects.
Each time we visit an object, we mark it in some way. 

Sweeping:
Once the mark phase completes, every reachable object in the heap has been marked.
That means any unmarked object is unreachable and ripe for reclamation.
We go through all the unmarked objects and free each one.
*/

void *gc_malloc(size_t size);
void gc_free(void *ptr);

#endif // !GC_H
