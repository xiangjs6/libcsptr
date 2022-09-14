#ifndef CSPTR_H
#define CSPTR_H

typedef void (*csptr_dtor_t)(void *);
#ifdef _CSPTR_SOURCE
struct {
    void *(*alloc)(size_t);
    void (*dealloc)(void *);
} csptr_allocator = {.alloc = malloc, .dealloc = free};
#else
extern struct {
    void *(*alloc)(size_t);
    void (*dealloc)(void *);
} csptr_allocator;
#endif

extern void *csptr_malloc(size_t, csptr_dtor_t);
extern void csptr_free(void *);
extern void *csptr_ref(void *);
#endif // CSPTR_H
