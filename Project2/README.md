# Project 2
---
## Group Members
Arifulla Shaik (arifullashaik@csu.fullerton.edu)

Angarag Gansukh (angaraggansukh@csu.fullerton.edu)

Lea Albano (leaalbano@csu.fullerton.edu)

---
# malloc()
Our implementation of malloc uses a linked list to implement the free list. The linked list will contain the size of allocated memory and a pointer to keep track of the heap memory. We will add to the free list in increasing order of memory address; this way we have a list of continuous memory blocks. When malloc gets called, we first find a memory block enough for the size requested and call the firstfit() function, which will traverse the free list and try to find a block that's equal to or larger than the memory requested and then return that block. Then, we will update the heap size and return the memory block we got from our first fit function 
within our malloc function. Also, we keep track of the memory blocks in a hash map, since we want to be able to locate the block when we free the block from our free list. 

---
# free() 
We implement free by trying to find the memory block to free within out hash map that contains all the memory blocks. Once found, we call our add to free list function and insert it where it belongs based on the memory address. After we add to the free list, we will call a function to coalesce our free list. Since we stored the memory blocks in continuous addresses, we calculate if two memory blocks are continuous addresses and if they are, we merge them. 
