#include <cstddef>
#include <cstdlib>
#include "alloc.h"

LinearAllocator::LinearAllocator(size_t maxSize): maxSize(maxSize), occupied(0)
{
    if (maxSize == 0) {
        memPtr = nullptr;
    } else {
        memPtr = (char *) malloc(maxSize * sizeof(char));
        if (memPtr == nullptr) {
            this->maxSize = 0;
        }
    }
}

LinearAllocator::~LinearAllocator()
{
    free(memPtr);
}

char* LinearAllocator::alloc(size_t size)
{
    if (size + occupied > maxSize) {
        return nullptr;
    }
    size_t oldOccupied = occupied;
    occupied += size;
    return memPtr + oldOccupied;
}

void LinearAllocator::reset()
{
    occupied = 0;
}
