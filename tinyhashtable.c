/**
hash表
1.冲突解决方案采用链表
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tinyhashtable.h"

/**ELFhash*/
int hash_calc(char* str, int size)
{
   unsigned int hash = 0;
   unsigned int x    = 0;

   while(*str) {
      hash = (hash << 4) + (*str++);
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash % size;
}

int hash_insert(struct HashNode *arr, char *key, void *value)
{
	int pos						= 0;
    struct Node *conflict		= NULL;

    if (!arr || !key || !value) {
    	return -1;
	}
	if (arr->size <= arr->length) {
		arr->rehash(arr);
	}
	pos			= hash_calc(key, arr->size);
	printf("insert pos:%d/%d\n", pos, arr->size);
	conflict	= &arr->node[pos];
	while(conflict && conflict->key) {
        if (!strcmp(conflict->key, key)) {
			conflict->value = value;
			return 0;
        }
        if (conflict->next) {
            conflict = conflict->next;
        } else {
            conflict->next = calloc(1, sizeof(struct Node));
            if (!conflict->next) {
				return -2;
            }
            conflict = conflict->next;
        }
	}
    conflict->key	= key;
    conflict->value	= value;
    conflict->next	= NULL;
	arr->length++;
    return 0;
}

struct Node *hash_find(struct HashNode *arr, char *key)
{
    int pos					= 0;
    struct Node *conflict	= NULL;

	if (!arr || !key) {
		return NULL;
	}
	pos = hash_calc(key, arr->size);

	printf("find pos :%d\t", pos);
    conflict = &arr->node[pos];
    while (conflict && conflict->key) {
        if (!strcmp(conflict->key, key)) {
			return conflict;
        }
        conflict = conflict->next;
    }
    return NULL;
}

int hash_delete(struct HashNode *arr, char *key)
{
	int pos					= 0;
    struct Node *conflict	= NULL;
    struct Node *cur		= NULL;

	if (!arr || !key) {
		return -1;
	}
	pos = hash_calc(key, arr->size);
	printf("delete pos: %d\n", pos);
    conflict = &arr->node[pos];
    if (conflict && !strcmp(conflict->key, key)) {
			if (conflict->next) {
				struct Node *tmp	= conflict->next;
				conflict->key		= tmp->key;
				conflict->value		= tmp->value;
				conflict->next		= tmp->next;
				free(tmp);
			} else {
				conflict->key	= NULL;
				conflict->value	= NULL;
			}
			arr->length--;
			return 0;
	}

    while (conflict && conflict->key) {
        if (!strcmp(conflict->key, key)) {
			if (conflict->next) {
				cur->next = conflict->next;
			}
			free(conflict);
			arr->length--;
			return 0;
        }
        cur = conflict;
        conflict = conflict->next;
    }

    return -1;
}

int hash_free(struct HashNode *header)
{
	int i				= 0;
	struct Node *tmp	= NULL;
	struct Node *cur = NULL;

	if (!header) {
		return -1;
	}
	tmp = header->node;
	for (i = 0; i < header->size; i++) {
		if (tmp[i].key && (cur = tmp[i].next)) {
			struct Node *pre = NULL;

			while (cur) {
                pre = cur->next;
                free(cur);
				printf("free conflict pos: %d\n", i);
                cur = NULL;
                cur = pre;
			}
		}
	}
    free(tmp);
	printf("free done!\n");
    return 0;
}

int hash_init(struct HashNode* hnode)
{
	struct Node* buf = NULL;

    if (!hnode) {
		printf("HashNode init failed\n");
    }
    buf = calloc(ALLOCSIZE, sizeof(struct Node));
    if (!buf) {
		printf("Node init failed\n");
		return -1;
    }
    hnode->node = buf;
    return 0;
}

int rehash(struct HashNode *arr)
{
	int i					= 0;
	int oldsize				= 0;
	int newsize				= 0;
	struct HashNode *swap	= NULL;
	if (!arr) {
		return -1;
	}

	oldsize	= arr->size;
	swap	= calloc(1, sizeof(struct HashNode));
	if (!swap) {
		return -1;
	}
	swap->size = oldsize;
	swap->node = calloc(oldsize, sizeof(struct Node));
	if (!swap->node) {
		free(swap);
		return -1;
	}
	memcpy(swap->node, arr->node, oldsize * sizeof(struct Node));

	newsize = oldsize + ALLOCSIZE;
    arr->node = realloc(arr->node, newsize * sizeof(struct Node));
    if (!arr->node) {
		free(swap->node);
		free(swap);
		return -1;
    }
	memset(arr->node, 0, newsize * sizeof(struct Node));

	arr->size = newsize;
	arr->length = 0;

	for (i = 0; i < oldsize; i++) {
		struct Node *cur = NULL;

		cur = &swap->node[i];
        while (cur && cur->key) {
            arr->hash_insert(arr, cur->key, cur->value);
            cur = cur->next;
        }
	}
	swap->hash_free = &hash_free;
	swap->hash_free(swap);
	return 0;
}
