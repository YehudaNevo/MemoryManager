#ifndef MEMORYMANAGER_SEGMENTEDFREELISTALLOCATOR_H
#define MEMORYMANAGER_SEGMENTEDFREELISTALLOCATOR_H

#include "IMemoryAllocator.h"
#include "MemoryBlock.h"

class SegmentedFreeListAllocator : public IMemoryAllocator {

private:
    MemoryBlock* smallBlocks;
    MemoryBlock* mediumBlocks;
    MemoryBlock* largeBlocks;

public:
    SegmentedFreeListAllocator()
            : smallBlocks(nullptr), mediumBlocks(nullptr), largeBlocks(nullptr) {}

    virtual void* allocate(size_t size) override;
    virtual void deallocate(void* pointer) override;

    ~SegmentedFreeListAllocator() {
        // Cleanup logic to free all lists
    }
};
#endif //MEMORYMANAGER_SEGMENTEDFREELISTALLOCATOR_H
