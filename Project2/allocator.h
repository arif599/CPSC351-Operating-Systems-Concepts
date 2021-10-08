#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <cstddef>
#include <map>

using namespace std;

const auto KB = 1024;

//Node for Free list
class Node{
    public:
        std::byte *address;
        size_t len;
        Node *next;
};

// Free list implementation
class FreeList{
    public:
        Node* head;

    public:
        void initialize(std::byte *allocatedHeap, size_t size);
        std::byte* firstFit(size_t size);
        void printList();
        void afterFree();
        void addFree(std::byte *freedAddress, size_t size);
        ~FreeList();
};


class Allocator
{
public:
    static const auto DEFAULT_MEMORY_SIZE = 4 * KB;

    Allocator(size_t size = DEFAULT_MEMORY_SIZE);
    ~Allocator();
    std::byte *malloc(size_t);
    void free(std::byte *ptr);
    void dump();

public:
    size_t heap_size;
    std::byte *heap;
    FreeList list;
    std::map<std::byte*, size_t> blockMap;
};

#endif
