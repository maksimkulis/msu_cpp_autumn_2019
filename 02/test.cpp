#include <iostream>

#include "alloc.h"

int main()
{
    LinearAllocator allocator = LinearAllocator(6);
    char* arr1 = allocator.alloc(3);
    if (arr1 != nullptr) {
        std::cout << "Test0 OK\n";
    } else {
        std::cout << "Test0 FAIL\n";
        return -1;
    }
    char* arr2 = allocator.alloc(2);
    if (arr1 + 3 == arr2) {
        std::cout << "Test1 OK\n";
    } else {
        std::cout << "Test1 FAIL\n";
        return -1;
    }
    char* arr3 = allocator.alloc(100);
    if (arr3 == nullptr) {
        std::cout << "Test2 OK\n";
    } else {
        std::cout << "Test2 FAIL\n";
        return -1;
    }
    allocator.reset();
    char* arr4 = allocator.alloc(5);
    if (arr4 != nullptr) {
        std::cout << "Test3 OK\n";
    } else {
        std::cout << "Test3 FAIL\n";
        return -1;
    }
    if (arr4 == arr1) {
        std::cout << "Test4 OK\n";
    } else {
        std::cout << "Test4 FAIL\n";
        return -1;
    }
    return 0;
}
