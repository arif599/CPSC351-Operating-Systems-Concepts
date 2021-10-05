#include <cassert>

#include <iomanip>
#include <iostream>

#include "allocator.h"

using std::cerr;
using std::endl;

//Placed in memory right before allocation happens
struct header_block{
    int size;
    int magic; 
};

//Free list implementation 
struct free_list{
    int size;
    free_list *next; 
};


Allocator::Allocator(size_t size)
{
    heap = new std::byte[size]();
    assert(heap != NULL);

    this->heap_size = size;
    
    //Initialize free list 
    free_list *head = heap;
    head->size = size - sizeof(free_list);
    head->next = NULL;
}

Allocator::~Allocator()
{
    delete[] heap;
}

std::byte *Allocator::malloc(size_t size)
{
    assert(size > 0 && size <= heap_size);

    return &(heap[0]);
}

void Allocator::free(std::byte *ptr)
{
    assert(ptr != NULL);
}

void Allocator::dump()
{
    cerr << std::hex << std::uppercase << std::setfill('0');
    for (size_t i = 1; i <= heap_size; i++)
    {
        auto offset = i - 1;
        if (offset % 16 == 0)
        {
            cerr << std::setw(3) << offset << ": ";
        }
        cerr << std::setw(2) << static_cast<unsigned int>(heap[offset]);
        if (i % 16 == 0)
        {
            cerr << endl;
        }
        else
        {
            cerr << ' ';
        }
    }
}
