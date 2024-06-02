#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include "types.h"
#include "str.h"

#define LOAD_FACTOR (0.75)

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

Hash_Table* hash_table_insert(Hash_Table* h, const char* key, i32 value);
Hash_Table* hash_table_delete(Hash_Table* h, const char* key);
bool hash_table_search(Hash_Table* h, const char* key);
i32 hash_table_get(Hash_Table* h, const char* key);
Hash_Table* hash_table_init(u64 initial_size);
void hash_table_destroy(Hash_Table* h);

#endif  // HASHTABLE_H
