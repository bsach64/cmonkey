#include "types.h"
#include "hashtable.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static u64 hash(const char* key, u64 size)
{
	u32 hash = 2166136261u;
	for (u64 i = 0; i < size; i++) {
		hash ^= (u8)key[i];
		hash *= 16777619;
	}
	return (u64)hash;
}

static hash_table* hash_table_rebuild(hash_table* h, u64 new_size)
{
	hash_table* new_h = hash_table_init(new_size);
	for (u64 i = 0; i < h->size; i++) {
		if (h->entries[i].empty || h->entries[i].delete_me)
			continue;
		new_h = hash_table_insert(new_h, h->entries[i].key->str, h->entries[i].value);
	}
	hash_table_destroy(h);
	return new_h;
}

hash_table* hash_table_init(u64 initial_size)
{
	hash_table* h = malloc(sizeof(*h));
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

void hash_table_destroy(hash_table* h)
{
	for (u64 i = 0; i < h->size; i++) {
		if (h->entries[i].empty)
			continue;
		free(h->entries[i].key->str);
		free(h->entries[i].key);
	}
	free(h->entries);
	free(h);
}

hash_table* hash_table_insert(hash_table* h, const char* key, i32 value)
{
	u64 length = strlen(key);
	char* ckey = malloc(length + 1);
	memcpy(ckey, key, length + 1);

	h->filled += 1;
	u64 i = hash(ckey, length) % h->size;
	while(!h->entries[i].empty || !h->entries[i].delete_me) {
		if (h->entries[i].key->size == length && strncmp(h->entries[i].key->str, ckey, length) == 0) {
			h->entries[i].value = value;
			free(ckey);
			return h;
		}
		i = (i + 1) % h->size;
	}
	h->entries[i].value = value;
	h->entries[i].empty = false;
	h->entries[i].delete_me = false;

	h->entries[i].key = malloc(sizeof(*(h->entries[i].key)));
	h->entries[i].key->size = length;
	h->entries[i].key->str = ckey;
	
	if ((h->filled / (double) h->size) > LOAD_FACTOR) {
		hash_table* new_h = hash_table_rebuild(h, h->size * 2);
		h = new_h;
	}
	
	return h;
}

hash_table* hash_table_delete(hash_table* h, const char* key)
{
	u64 key_len = strlen(key);
	u64 i = hash(key, key_len) % h->size;
	
	while(!h->entries[i].empty) {
		if (!h->entries[i].delete_me && h->entries[i].key->size == key_len
			&& strncmp(h->entries[i].key->str, key, key_len) == 0) {
			h->entries[i].delete_me = true;
			h->filled -= 1;
			break;
		}
		i = (i + 1) % h->size;
	}

	if (h->filled > 0 && h->filled / (double) h->size <= (double) 0.2500) {
		h = hash_table_rebuild(h, h->size / 2);
	}
	return h;
}

bool hash_table_search(hash_table* h, const char* key)
{
	u64 key_len = strlen(key);
	u64 i = hash(key, key_len) % h->size;
	
	while(!h->entries[i].empty) {
		if (!h->entries[i].delete_me && h->entries[i].key->size == key_len
			&& strncmp(h->entries[i].key->str, key, key_len) == 0) {
			return true;
		}
		i = (i + 1) % h->size;
	}
	return false;
}

i32 hash_table_get(hash_table* h, const char* key)
{
	u64 key_len = strlen(key);
	u64 i = hash(key, key_len) % h->size;
	
	while(!h->entries[i].empty) {
		if (!h->entries[i].delete_me && h->entries[i].key->size == key_len
			&& strncmp(h->entries[i].key->str, key, key_len) == 0) {
			return h->entries[i].value;
		}
		i = (i + 1) % h->size;
	}
	return 0;
}
