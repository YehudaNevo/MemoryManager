#ifndef MEMORYMANAGER_IMEMORYALLOCATOR_H
#define MEMORYMANAGER_IMEMORYALLOCATOR_H
#include <cstddef>

// interface for mem allocator
class IMemoryAllocator {
public:
    virtual void* allocate(size_t size) = 0;
    virtual void deallocate(void* pointer) = 0;
    virtual ~IMemoryAllocator() = default;
};


#endif //MEMORYMANAGER_IMEMORYALLOCATOR_H
