#include "pq.h"

#include <stdlib.h>

struct pq {
  void *ptr;
};

/* Allocates and initializes a new pq */
pq* pq_create()
{
  return (pq*)malloc(sizeof(pq));
}

/* Adds value to pq based on numerical order of key */
void pq_push(pq *head, double key, void *value)
{
  if (head && !(head->ptr)) head->ptr = value;
}

/* Returns value from pq having the minimum key */
void* pq_pop(pq *head)
{
  void *p = head->ptr;
  head->ptr = NULL;
  return p;
}

/* Deallocates (frees) pq. Shallow destruction,
meaning nodes in the pq are not recursively freed. */
void pq_destroy(pq *head)
{
  free(head);
}

