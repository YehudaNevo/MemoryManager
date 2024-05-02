#ifndef MEMORYMANAGER_MEMORYBLOCK_H
#define MEMORYMANAGER_MEMORYBLOCK_H
#include <cstddef>

// the base NODE in the linked list of the segment list alloc is memory block...
class MemoryBlock {
public:
    size_t size;
    void* address;
    MemoryBlock* next;

    MemoryBlock(size_t sz, void* addr, MemoryBlock* nxt = nullptr)
            : size(sz), address(addr), next(nxt) {}
};

#endif //MEMORYMANAGER_MEMORYBLOCK_H
