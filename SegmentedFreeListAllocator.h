#ifndef MEMORYMANAGER_SEGMENTEDFREELISTALLOCATOR_H
#define MEMORYMANAGER_SEGMENTEDFREELISTALLOCATOR_H
#include <cstdlib>
#include <iostream>
#include "IMemoryAllocator.h"
#include "MemoryBlock.h"

class SegmentedFreeListAllocator {

private:
    // pointers
    MemoryBlock *initialMemory;
    MemoryBlock *smallBlocks;
    MemoryBlock *mediumBlocks;
    MemoryBlock *largeBlocks;
    // size of the blocks ( maybe put as const in cons file ? )
    static constexpr size_t SMALL_BLOCK_SIZE = 128;
    static constexpr size_t MEDIUM_BLOCK_SIZE = 1024;
    static constexpr size_t LARGE_BLOCK_SIZE = 4096;

public:

    // Constructor
    inline explicit SegmentedFreeListAllocator(size_t totalSize)
            : smallBlocks(nullptr), mediumBlocks(nullptr), largeBlocks(nullptr) {

        // 1. Allocate the total size
        initialMemory = reinterpret_cast<MemoryBlock *>(malloc(totalSize));
        if (!initialMemory) return;  // Check for malloc failure

        // 2. Divide the allocated memory into block lists
        size_t numSmallBlocks = (totalSize / 3) / SMALL_BLOCK_SIZE;
        size_t numMediumBlocks = (totalSize / 3) / MEDIUM_BLOCK_SIZE;
        size_t numLargeBlocks = (totalSize / 3) / LARGE_BLOCK_SIZE;

        // max unused will be sum of each (block size -1 ) + 2
        std::cout << "Unused memory: " << totalSize - ((numSmallBlocks * SMALL_BLOCK_SIZE) +
        (numMediumBlocks * MEDIUM_BLOCK_SIZE) +
        (numLargeBlocks * LARGE_BLOCK_SIZE)) << " bytes" << std::endl;


        // Initialize small blocks
        smallBlocks = initializeBlocks(initialMemory, SMALL_BLOCK_SIZE, numSmallBlocks);

        // Initialize medium blocks
        mediumBlocks = initializeBlocks(reinterpret_cast<MemoryBlock *>(
                                                reinterpret_cast<char *>(smallBlocks) +
                                                numSmallBlocks * SMALL_BLOCK_SIZE),
                                        MEDIUM_BLOCK_SIZE, numMediumBlocks);

        // Initialize large blocks
        largeBlocks = initializeBlocks(reinterpret_cast<MemoryBlock *>(
                                               reinterpret_cast<char *>(mediumBlocks) +
                                               numMediumBlocks * MEDIUM_BLOCK_SIZE),
                                       LARGE_BLOCK_SIZE, numLargeBlocks);
    }

    // Destructor
    ~SegmentedFreeListAllocator() {
        free(initialMemory);  // Free the initially allocated block
    }



    static void *allocate(size_t size){
        return nullptr;
    };

    void deallocate(void *pointer) {};

    // Helper function to initialize blocks
    static MemoryBlock* initializeBlocks(MemoryBlock* start, size_t blockSize, size_t count) {
        MemoryBlock* head = nullptr;
        MemoryBlock* current = nullptr;

        for (size_t i = 0; i < count; ++i) {
            MemoryBlock* block = reinterpret_cast<MemoryBlock*>(
                    reinterpret_cast<char*>(start) + i * blockSize);
            block->size = blockSize;
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
