#include <cassert>

#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include "allocator.h"
using namespace std;


Allocator::Allocator(size_t size)
{
    heap = new std::byte[size]();
    assert(heap != NULL);
    heap_size = size;
    //cout << heap_size << endl;
    list.initialize(heap, size);


}

Allocator::~Allocator()
{
    delete[] heap;
    // delete& list;
    // delete& blockMap;
}

std::byte *Allocator::malloc(size_t size)
{
      
    if(size > 0 && size <= heap_size){
      std::byte *currHeap = list.firstFit(size);
      heap = currHeap;
      heap_size -= size;

      blockMap.insert(pair<std::byte*, size_t>(&(currHeap[0]), size));
      cout << "\tHashMap " << &(currHeap[0]) << " : " << size << endl;
     
      cout << "\tBefore adding: " << &(currHeap[0]) << endl;
      cout << "\tAfter adding " << size << ": " << &(currHeap[0])+size << endl;
      //cout << "printing list from malloc" << endl;
      //list.print();
      return &(currHeap[0]);
    }



    
    return NULL;

}


void Allocator::free(std::byte *ptr)
{
    //cout << "printing list from free" << endl;
    //list.print();
    assert(ptr != NULL);
    cout << "\n\tPTR POINTER: " << ptr << endl;

    map<std::byte*, size_t>::iterator it ;
    it = blockMap.find(ptr);
      
    if(it == blockMap.end())
        cout << "Key-value pair not present in map" ;
    else
        cout << "Key-value pair present : " 
          << it->first << "->" << it->second << endl;

    list.addFree(ptr, it->second);
    heap_size += it->second;
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

