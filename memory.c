#include <carl/memory.h>
#include <carl/sys.h>

static uint8_t* heap_base = (uint8_t*)0x400000;   // 4MB mark
static uint8_t* heap_ptr  = (uint8_t*)0x400000;   // current pointer
static uint8_t* heap_end  = (uint8_t*)0x800000;   // 8MB mark

void* c_allocate_memory(size_t size) {
    if (heap_ptr + size >= heap_end)
        return NULL; // Out of memory

    void* block = heap_ptr;
    heap_ptr += size;

    return block;
}

void c_free_memory(void* memory) {
    // In this simple implementation, we do not support freeing individual blocks.
    // Memory is only freed when the entire heap is reset or the program ends.
}

// ============================================================
// Virtual memory allocator (page-based)
// ============================================================

void* c_virtual_alloc(size_t size) {
    return c_VirtualAlloc(size);
}

void c_virtual_free(void* address) {
    c_VirtualFree(address);
}