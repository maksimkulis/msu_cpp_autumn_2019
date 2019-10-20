#pragma once


class LinearAllocator
{
public:
    LinearAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~LinearAllocator();
private:
    char* memPtr;
    size_t maxSize;
    size_t occupied;
};
