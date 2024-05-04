#include <iostream>
#include "SegmentedFreeListAllocator.h"

int main() {
    // Create an allocator with a total size of 1 MB
    SegmentedFreeListAllocator allocator(1024 * 1024); // 1 MB total size

    // Example allocations
    void* ptr1 = allocator.allocate(50);  // Small block
    void* ptr2 = allocator.allocate(500); // Small block
    void* ptr3 = allocator.allocate(800); // Medium block
    void* ptr4 = allocator.allocate(2000); // Medium block
    void* ptr5 = allocator.allocate(3000); // Large block

    std::cout << "Allocated blocks:" << std::endl;
    std::cout << "ptr1: " << ptr1 << std::endl;
    std::cout << "ptr2: " << ptr2 << std::endl;
    std::cout << "ptr3: " << ptr3 << std::endl;
    std::cout << "ptr4: " << ptr4 << std::endl;
    std::cout << "ptr5: " << ptr5 << std::endl;

    // Deallocate some blocks
    std::cout << "\nDeallocating ptr1, ptr3, and ptr5." << std::endl;
    allocator.deallocate(ptr1);
    allocator.deallocate(ptr3);
    allocator.deallocate(ptr5);

    // Allocate again to check if freed blocks are reused
    void* ptr6 = allocator.allocate(50);  // Should reuse the block freed from ptr1
    void* ptr7 = allocator.allocate(800); // Should reuse the block freed from ptr3

    std::cout << "Reallocated blocks after deallocation:" << std::endl;
    std::cout << "ptr6 (reuse of ptr1): " << ptr6 << std::endl;
    std::cout << "ptr7 (reuse of ptr3): " << ptr7 << std::endl;

    return 0;
}
