#ifndef CARL_MEMORY_H
#define CARL_MEMORY_H

void* c_allocate_memory(size_t size);
void c_free_memory(void* memory);
void* c_virtual_alloc(size_t size);
void c_virtual_free(void* address);

#endif /* CARL_MEMORY_H */
