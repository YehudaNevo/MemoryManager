#ifndef MEMORYMANAGER_SEGMENTEDFREELISTALLOCATOR_H
#define MEMORYMANAGER_SEGMENTEDFREELISTALLOCATOR_H

#include <cstdlib>
#include <iostream>
#include "IMemoryAllocator.h"
#include "MemoryBlock.h"

class SegmentedFreeListAllocator {
private:
    // Pointers
    MemoryBlock *initialMemory;
    MemoryBlock *smallBlocks;
    MemoryBlock *mediumBlocks;
    MemoryBlock *largeBlocks;

    // Size of the blocks (consider putting as const in config file?)
    static constexpr size_t SMALL_BLOCK_SIZE = 128 + sizeof(size_t);
    static constexpr size_t MEDIUM_BLOCK_SIZE = 1024 + sizeof(size_t);
    static constexpr size_t LARGE_BLOCK_SIZE = 4096 + sizeof(size_t);

public:
    // Constructor
    explicit SegmentedFreeListAllocator(size_t totalSize)
            : smallBlocks(nullptr), mediumBlocks(nullptr), largeBlocks(nullptr) {
        initialMemory = reinterpret_cast<MemoryBlock *>(malloc(totalSize));
        if (!initialMemory) return;  // Check for malloc failure

        // Initialize block lists
        smallBlocks = initializeBlocks(initialMemory, SMALL_BLOCK_SIZE, (totalSize / 3) / SMALL_BLOCK_SIZE);
        mediumBlocks = initializeBlocks(reinterpret_cast<MemoryBlock *>(reinterpret_cast<char *>(smallBlocks) + (totalSize / 3)),
                                        MEDIUM_BLOCK_SIZE, (totalSize / 3) / MEDIUM_BLOCK_SIZE);
        largeBlocks = initializeBlocks(reinterpret_cast<MemoryBlock *>(reinterpret_cast<char *>(mediumBlocks) + (totalSize / 3)),
                                       LARGE_BLOCK_SIZE, (totalSize / 3) / LARGE_BLOCK_SIZE);
    }

    // Destructor
    ~SegmentedFreeListAllocator() {
        free(initialMemory);
    }

    void* allocate(size_t size) {
        MemoryBlock* blockToUse = nullptr;
        if (size <= SMALL_BLOCK_SIZE - sizeof(size_t)) {
            blockToUse = smallBlocks;
            if (blockToUse) smallBlocks = smallBlocks->next;
        } else if (size <= MEDIUM_BLOCK_SIZE - sizeof(size_t)) {
            blockToUse = mediumBlocks;
            if (blockToUse) mediumBlocks = mediumBlocks->next;
        } else if (size <= LARGE_BLOCK_SIZE - sizeof(size_t)) {
            blockToUse = largeBlocks;
            if (blockToUse) largeBlocks = largeBlocks->next;
        }

        if (blockToUse) {
            // Store size at the beginning of the block
            *reinterpret_cast<size_t*>(blockToUse) = size;
            // Return the address right after the size
            return reinterpret_cast<void*>(reinterpret_cast<char*>(blockToUse) + sizeof(size_t));
        }

        return nullptr;
    }

    void deallocate(void* pointer) {
        if (!pointer) return;
        // Get the actual start of the block
        MemoryBlock* block = reinterpret_cast<MemoryBlock*>(reinterpret_cast<char*>(pointer) - sizeof(size_t));

        // Check size and add block back to the appropriate list
        size_t size = block->size;
        block->next = (size <= SMALL_BLOCK_SIZE - sizeof(size_t)) ? smallBlocks :
                      (size <= MEDIUM_BLOCK_SIZE - sizeof(size_t)) ? mediumBlocks : largeBlocks;

        if (size <= SMALL_BLOCK_SIZE - sizeof(size_t)) {
            smallBlocks = block;
        } else if (size <= MEDIUM_BLOCK_SIZE - sizeof(size_t)) {
            mediumBlocks = block;
        } else if (size <= LARGE_BLOCK_SIZE - sizeof(size_t)) {
            largeBlocks = block;
        }
    }

    // Helper function to initialize blocks
    static MemoryBlock* initializeBlocks(MemoryBlock* start, size_t blockSize, size_t count) {
        MemoryBlock* head = nullptr;
        MemoryBlock* current = nullptr;

        for (size_t i = 0; i < count; ++i) {
            MemoryBlock* block = reinterpret_cast<MemoryBlock*>(reinterpret_cast<char*>(start) + i * blockSize);
            block->size = blockSize - sizeof(size_t);  // Adjust size to exclude metadata
            block->next = nullptr;

            if (head == nullptr) {
                head = block;
            } else {
                current->next = block;
            }
            current = block;
        }
        return head;
    }
};

#endif //MEMORYMANAGER_SEGMENTEDFREELISTALLOCATOR_H
