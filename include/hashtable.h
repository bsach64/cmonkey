#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include "types.h"
#include "str.h"

#define LOAD_FACTOR (0.75)

typedef struct {
	string* key;
	i32 value;
	bool delete_me;
	bool empty;
} hash_table_entry;

typedef struct {
	hash_table_entry* entries;
	u64 size;
	u64 filled;
} hash_table;

hash_table* hash_table_insert(hash_table* h, const char* key, i32 value);
hash_table* hash_table_delete(hash_table* h, const char* key);
bool hash_table_search(hash_table* h, const char* key);
i32 hash_table_get(hash_table* h, const char* key);
hash_table* hash_table_init(u64 initial_size);
void hash_table_destroy(hash_table* h);

#endif  // HASHTABLE_H
