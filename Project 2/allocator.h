#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>

const auto KB = 1024;

class Allocator
{
public:
    static const auto DEFAULT_MEMORY_SIZE = 4 * KB;

    Allocator(size_t size = DEFAULT_MEMORY_SIZE);
    ~Allocator();

    std::byte *malloc(size_t);
    void free(std::byte *);

    void dump();

private:
    size_t heap_size;
    std::byte *heap;
};

#endif
