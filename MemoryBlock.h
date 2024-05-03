#ifndef MEMORYMANAGER_MEMORYBLOCK_H
#define MEMORYMANAGER_MEMORYBLOCK_H
#include <cstddef>

class MemoryBlock {
public:
    size_t size;
    void* address;
    MemoryBlock* next;

   inline MemoryBlock(size_t sz, void* addr, MemoryBlock* nxt = nullptr)
            : size(sz), address(addr), next(nxt) {}
};

#endif //MEMORYMANAGER_MEMORYBLOCK_H
