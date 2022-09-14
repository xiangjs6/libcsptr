#include <stdatomic.h>
#include <stdlib.h>
#include <stddef.h>

#define _CSPTR_SOURCE
#include "csptr.h"

typedef struct {
    atomic_ullong ref;
    csptr_dtor_t dtor;
    char ptr[];
} csptr_t;

void *csptr_malloc(size_t size, csptr_dtor_t dtor)
{
    csptr_t *ptr = (csptr_t *)csptr_allocator.alloc(size + sizeof(csptr_t));
    if (ptr == NULL) {
        return NULL;
    }
    ptr->dtor = dtor;
    atomic_store(&ptr->ref, 1);
    return ptr->ptr;
}

void csptr_free(void *_p)
{
    csptr_t *ptr = (csptr_t *)((char *)_p - offsetof(csptr_t, ptr));
    if (atomic_fetch_sub(&ptr->ref, 1) == 1) {
        if (ptr->dtor != NULL) {
            ptr->dtor(ptr->ptr);
        }
        csptr_allocator.dealloc(ptr);
    }
}

void *csptr_ref(void *_p)
{
    csptr_t *ptr = (csptr_t *)((char *)_p - offsetof(csptr_t, ptr));
    atomic_fetch_add(&ptr->ref, 1);
    return ptr->ptr;
}
