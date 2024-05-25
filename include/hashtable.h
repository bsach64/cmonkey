#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include "str.h"
#include "types.h"

/*
* insert: insert a (key, value)
* search: given a key and return its value
* delete: given a key delete its value
*/

typedef struct {
	i32 value;
	bool delete_me;
	bool empty;

} Hash_Table_Entry;


typedef struct {
	Arena* arena;
	Hash_Table_Entry* entries;
	u64 m;
} Hash_Table;

u64 prehash(Str key);
u64 hash(u64 prehashed_key);
void insert(Hash_Table* hash_table, Str key, i32 value);
bool delete(Hash_Table* hash_table, Str key);
bool search(Hash_Table* hash_table, Str key);
Hash_Table* hash_table_init(Arena* arena);
void hash_table_print(Hash_Table* hash_table);

#endif  // INCLUDE_INCLUDE_HASHTABLE_H_
