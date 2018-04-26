#ifndef __TINY_HASH_TABLE__
#define __TINY_HASH_TABLE__

#define ALLOCSIZE 5

struct Node {
    void *value;
    char *key;
    struct Node* next;
};

struct HashNode {
	struct Node *node;
	int length;
	int size;
	int (*hash_init)(struct HashNode*);
    int (*hash_free)(struct HashNode*);
	int (*rehash)(struct HashNode*);
    int (*hash_insert)(struct HashNode*, char *, void *);
    int (*hash_delete)(struct HashNode*, char *);
    struct Node *(*hash_find)(struct HashNode*, char *);
};

int hash_calc(char* str, int size);
int hash_insert(struct HashNode *arr, char *key, void *value);
struct Node *hash_find(struct HashNode *arr, char *key);
int hash_delete(struct HashNode *arr, char *key);
int hash_free(struct HashNode *header);
int hash_init(struct HashNode* hnode);
int rehash(struct HashNode *arr);


#endif
