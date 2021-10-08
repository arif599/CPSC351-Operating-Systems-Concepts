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

    block->next = nullptr;
    block->prev = nullptr; 
    


    if(head == nullptr){
        head = block; 
        head->next = nullptr; 
    }
    else{
        if((unsigned long)head > (unsigned long)block){
            head->prev = block; 
            block->next = head;
            head = block; 
        }
        else{
            node_ptr * ptr = head; 
            while(ptr->next && (unsigned long)ptr->next < (unsigned long)block){
                ptr = ptr->next; 
            }
            ptr->next->prev = block;
            block->next = ptr->next; 
            ptr->next = block; 
            

        }
    }
   
        
}

void remove_from_list(node_ptr * block){

    if(block->prev == nullptr){
        if(block->next){
            head = block->next; 
        }
        else{
            head = nullptr; 
        }
    }
    else{
        block->prev->next = block->next;
    }
    if(block->next){
        block->next->prev = block->prev; 
    }

}

node_ptr * split_block(node_ptr * block, size_t size){

    node_ptr * memory_block = MEMORY_BLOCK(block);
    node_ptr * temp = (node_ptr *) ((unsigned long)memory_block + size); 
    temp->size = block->size - (size + sizeof(node_ptr)); 
    return temp; 

}

void coalesce(){

node_ptr * ptr = head;

while(ptr->next) {
    unsigned long current = (unsigned long)ptr; 
    unsigned long next = (unsigned long)ptr->next; 
    if((current + ptr->size + sizeof(node_ptr)) == next){
        ptr->size += ptr->next->size + sizeof(node_ptr);
        ptr->next = ptr->next->next; 
        if(ptr->next){
            ptr->next->prev = ptr; 
        }
        else{
           break;  
    }
}


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
    node_ptr * temp, *ptr, *ptr_1; 
    temp = list.head; 

    while(temp){
        if(temp->size >= size + sizeof(node_ptr)){
            ptr = MEMORY_BLOCK(temp);
            list.remove_from_list(temp);
            if(ptr->size == size) {
                return reinterpret_cast<byte *>(ptr); 
            }

            ptr_1 = split(temp,size);
            list.add_to_list(ptr_1);
            return reinterpret_cast<std::byte *>(ptr);

        }
        else {
            temp = temp->next; 
        }
    }

    return nullptr; 
}

void Allocator::free(std::byte *ptr)
{
    assert(ptr != NULL);
    list.add_to_list(HEADER_BLOCK(ptr));
    list.coalesce();

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
