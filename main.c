#include <stdio.h>
#include "tinyhashtable.h"

int main(int argc, char **argv)
{
	struct HashNode * tmp	= NULL;
	struct Node * print		= NULL;
	struct HashNode tb		= {
								NULL,
								0,
								ALLOCSIZE,
								hash_init,
								hash_free,
								rehash,
								hash_insert,
								hash_delete,
								hash_find
	};

	tmp = &tb;

	tb.hash_init(tmp);

//int hash_insert(struct HashNode *arr, char *key, void *value)
	tb.hash_insert(tmp, "key1", "syshaw1");
	tb.hash_insert(tmp, "key2", "syshaw2");
	tb.hash_insert(tmp, "key3", "syshaw3");
	tb.hash_insert(tmp, "key4", "syshaw4");
	tb.hash_insert(tmp, "key5", "syshaw5");
	tb.hash_insert(tmp, "key6", "syshaw6");
	tb.hash_insert(tmp, "key7", "syshaw7");
	tb.hash_insert(tmp, "key8", "syshaw8");
	tb.hash_insert(tmp, "key9", "syshaw9");
	tb.hash_insert(tmp, "key10", "syshaw10");
	tb.hash_insert(tmp, "key11", "syshaw11");
	printf("current len = %d\n", tmp->length);
	printf("\n\n");

	printf("%s\n", (print = tb.hash_find(tmp, "key1"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key2"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key3"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key4"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key5"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key6"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key7"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key8"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key9"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key10"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key11"))?(char *)print->value:"not found");

	printf("\n\n");

//struct Node *hash_find(struct HashNode *arr, char *key)
	printf("%s\n", (print = tb.hash_find(tmp, "key3"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key2"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key0"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key7"))?(char *)print->value:"not found");
	printf("\n\n");

//int hash_delete(struct HashNode *arr, char *key)
	tb.hash_delete(tmp, "key3");
	tb.hash_delete(tmp, "key4");
	tb.hash_delete(tmp, "key5");

	printf("current len = %d\n", tmp->length);

	printf("\n\n");
	printf("%s\n", (print = tb.hash_find(tmp, "key2"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key3"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key4"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key5"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key10"))?(char *)print->value:"not found");
	printf("%s\n", (print = tb.hash_find(tmp, "key11"))?(char *)print->value:"not found");

	printf("\n\n");
	tb.hash_free(tmp);

	return 0;
}
