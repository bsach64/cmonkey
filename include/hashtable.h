#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include "str.h"
#include "types.h"

#define LOAD_FACTOR (0.75)

/*
* insert: insert a (key, value)
* search: given a key and return its value
* delete: given a key delete its value
*/

typedef struct {
	Str* key;
	i32 value;
	bool delete_me;
	bool empty;
} Hash_Table_Entry;

typedef struct {
	Hash_Table_Entry* entries;
	u64 size;
	u64 filled;
} Hash_Table;

Hash_Table* insert(Hash_Table* h, Str* key, i32 value);
bool delete(Hash_Table* h, Str* key);
bool search(Hash_Table* h, Str* key);
Hash_Table* hash_table_init(u64 initial_size);
void hash_table_destroy(Hash_Table* h);

#endif  // HASHTABLE_H
