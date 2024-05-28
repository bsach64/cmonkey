#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "debug.h"
#include "types.h"

static u64 hash(Str key)
{
	u32 hash = 2166136261u;
	for (u64 i = 0; i < key.size; i++) {
		hash ^= (u8)key.str[i];
		hash *= 16777619;
	}
	return (u64)hash;
}

static Hash_Table* hash_table_copy(Hash_Table* h, u64 new_size)
{
	Hash_Table* new_h = hash_table_init(new_size);
	for (u64 i = 0; i < h->size; i++) {
		if (h->entries[i].empty)
			continue;
		insert(new_h, h->entries[i].key, h->entries[i].value);
	}
	return new_h;
}

Hash_Table* hash_table_init(u64 initial_size)
{
	Hash_Table* h = malloc(sizeof(*h));
	if (!h)
		goto malloc_fail;
	h->size = initial_size;
	h->filled = 0;
	h->entries = malloc(initial_size * (sizeof(*(h->entries))));
	if (!h->entries)
		goto malloc_fail;
	for (size_t i = 0; i < initial_size; i++) {
		h->entries[i].key = NULL;
		h->entries[i].value = 0;
		h->entries[i].empty = true;
		h->entries[i].delete_me = true;
	}
	return h;
malloc_fail:
	printf("ERROR: Could not allocate memory");
	exit(EXIT_FAILURE);
}

Hash_Table* insert(Hash_Table* h, Str* key, i32 value)
{
	if ((h->filled /(double) h->size) > LOAD_FACTOR) {
		Hash_Table* new_h = hash_table_copy(h, h->size * 2);
		h = new_h;
	}
	h->filled += 1;
	u64 i = hash(*key) % h->size;
	while (!h->entries[i].empty || !h->entries[i].delete_me)
		i = (i + 1) % h->size;
	h->entries[i].key = key;
	h->entries[i].empty = false;
	h->entries[i].delete_me = false;
	h->entries[i].value = value;
	return h;
}

void hash_table_destroy(Hash_Table* h)
{
	// memory used by keys should be freed separately
	free(h->entries);
	free(h);
}
