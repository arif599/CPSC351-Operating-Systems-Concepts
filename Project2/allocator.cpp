#include <cassert>

#include <iomanip>
#include <iostream>

#include "allocator.h"

using std::cerr;
using std::endl;

//MEMORY_BLOCK used to calculate how big of block to add
//HEADER_BLOCK used to calculate where a block resides in memory
//Cast to void* since we only want to know memory location 
#define MEMORY_BLOCK(ptr) (node_ptr*)((unsigned long)ptr + sizeof(free_list))
#define HEADER_BLOCK(ptr) (node_ptr*)unsigned long)ptr - sizeof(free_list))

//Placed in memory right before allocation happens
struct header_block{
    int size;
    int magic; 
};

struct node_ptr {
    node_ptr * next, *prev;
    size_t size; 
}
//Free list implementation 
class free_list{
    
    public:  
    node_ptr *head, *tail; 

    public:  

    void init(node_ptr * ptr,size_t size){

        ptr->size = size-sizeof(node_ptr);
        head = ptr; 
        tail = ptr;
        head->next = nullptr;
        head->prev = nullptr; 
        tail->next = nullptr; 
        tail->prev = nullptr; 
    }


    void add_to_list(node_ptr * block){

    assert(head != nullptr);
    block->next = nullptr;
    block->prev = nullptr; 
    node_ptr * node; 

    if((unsigned long)block < (unsigned long)head){
        head->prev = block; 
        block->next = head; 
        head = block; 
    }
    else{
        node = head; 
        while (node->next && ((unsigned long)curr->next < (unsigned long)block)){
            node = node->next; 
        }
        block->next = node->next;
        node->next = block; 
    }

   
        
}

void remove_from_list(free_list * block){

    
    if(head->next == nullptr){

        
    }
}

node_ptr * split_block(node_ptr * block, size_t size){

    node_ptr * memory_block = MEMORY_BLOCK(block);
    node_ptr * temp = (node_ptr *) ((unsigned long)memory_block + size); 
    temp->size = block->size - (size + sizeof(node_ptr)); 
    return temp; 

}

void coalesce(){

}



};

free_list list; 


Allocator::Allocator(size_t size)
{
    heap = new std::byte[size]();
    assert(heap != NULL);

    
    
    this->heap_size = size;

    node_ptr *ptr = reinterpret_cast<node_ptr *>(heap);
    list.init(ptr, size);  
    

}

Allocator::~Allocator()
{
    delete[] heap;
}

std::byte *Allocator::malloc(size_t size)
{
    assert(size > 0 && size <= heap_size);
    assert(list.head != nullptr);
    node_ptr * temp; 
    temp = list.head; 

    if(temp->next == nullptr){

        if(temp->size == (size + sizeof(node_ptr))){
            return temp.head; 
        }
        else if(temp->size > (size+sizeof(node_ptr))){
            node * ptr = list.split_block(temp,size);
            list.add_to_list(ptr); 
            return reinterpret_cast<std::byte *>(ptr); 
        }
        else {
            return nullptr; 
        }
    }
    else{ 
        if(temp->size == (size+sizeof(node_ptr))){
            list.remove_from_list(list.head);
            return 
        }
        
    }
    


    //return &(heap[0]);
    return list.head;
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
