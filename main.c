#include <stdlib.h>
#include <stdio.h>
#include "csptr.h"

void dtor_int(void *p)
{
    int *i = p;
    printf("dtor %p = %d\n", (void *)i, *i);
}

void *alloc(size_t size)
{
    void *p = malloc(size);
    printf("malloc %p\n", p);
    return p;
}

void dealloc(void *p)
{
    printf("free %p\n", p);
    free(p);
}

int main(void)
{
    csptr_allocator.alloc = alloc;
    csptr_allocator.dealloc = dealloc;
    int *some_int = csptr_malloc(sizeof(int), &dtor_int);
    *some_int = 1;

    printf("%p = %d\n", (void *)some_int, *some_int);

    *some_int = 2;
    csptr_free(some_int);
    return 0;
}
