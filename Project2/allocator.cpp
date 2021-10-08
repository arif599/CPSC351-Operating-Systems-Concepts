#include <cassert>

#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#include "allocator.h"
using namespace std;


// Allocator methods
Allocator::Allocator(size_t size)
{
    heap = new std::byte[size]();
    assert(heap != NULL);
    heap_size = size;
    list.initialize(heap, size);
}

Allocator::~Allocator()
{
    delete[] heap;
    list.~FreeList();
}

std::byte *Allocator::malloc(size_t size)
{
      
    if(size > 0 && size <= heap_size){
      std::byte *currHeap = list.firstFit(size);
      heap_size -= size;

      blockMap.insert(pair<std::byte*, size_t>(&(currHeap[0]), size));
      cout << "\tHashMap " << &(currHeap[0]) << " : " << size << endl;
     
      cout << "\tBefore adding: " << &(currHeap[0]) << endl;
      cout << "\tAfter adding " << size << ": " << &(currHeap[0])+size << endl;
      return &(currHeap[0]);
    }

    return NULL;
}


void Allocator::free(std::byte *ptr)
{

    assert(ptr != NULL);
    cout << "\n\tPTR POINTER: " << ptr << endl;

    map<std::byte*, size_t>::iterator it ;
    it = blockMap.find(ptr);

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

// Free list methods
void FreeList::initialize(std::byte *allocatedHeap, size_t size){
    head = nullptr;
    Node* newNode = new Node();
    newNode->address = allocatedHeap;
    newNode->len = size;
    newNode->next = NULL;
    head = newNode;
    
    cout << "\tINITIALIZING FREE LIST:" << endl;
    cout << "\t\tAddress - " << newNode->address << endl;
    cout << "\t\tLength - " << newNode->len << " KB" << endl;
}
    

std::byte* FreeList::firstFit(size_t size){
    // iterate thru the list and finds the first free segment
    // then returns a piece of the free segment based on the size requested
    Node* currNode = head;
    while(currNode != NULL){
        if(size <= currNode->len){
            std::byte *temp = currNode->address;
            currNode->address += size;
            currNode->len -= size;
            cout << "\n\tUPDATING FREE LIST:" << endl;
            cout << "\t\tAddress - " << currNode->address << endl;
            cout << "\t\tSize Requested - " << size << " KB" << endl;
            cout << "\t\tLength Remaining - " << currNode->len << " KB" << endl;
            return temp;
        }
        currNode = currNode->next;
    }
    return NULL;
}

void FreeList::printList(){
  Node* currNode = head;
  int i = 0;
    while(currNode != NULL){
      cout << "Node " << i << ":" << endl;
      cout << "\tAddress - " << currNode->address << endl;
      cout << "\tSize - " << currNode->len << endl;

      cout << "\tAddress + size - " << currNode->address + currNode->len << endl;
      //cout << "\tNext Address - " << currNode->next->address << endl;
      currNode = currNode->next;
      i++;
    }
}

void FreeList::afterFree(){
    // merge any blocks of free spaces
    Node *currNode = head;
    while(currNode != NULL){
      std::byte *sum = currNode->address + currNode->len;
      while(currNode->next != NULL && sum == currNode->next->address){
          // merge blocks
          currNode->len += currNode->next->len;
          if(currNode->next->next != NULL){
            Node *tempNode = currNode->next;
            currNode->next = currNode->next->next;
            delete tempNode;
          }else{
            currNode->next = NULL;
          }
        sum = currNode->address + currNode->len;
      }
      currNode = currNode->next;
    }
}

void FreeList::addFree(std::byte *freedAddress, size_t size){
    Node *currNode = head;

    if (freedAddress < head->address)
    {
        // add infront of head
        Node* newNode = new Node();
        newNode->address = freedAddress;
        newNode->len = size;
        newNode->next = head;
        head = newNode;
    }
    else
    {
        while (currNode != NULL)
        {
            if (currNode->next == NULL)
            {
                // adding new node to  the linked list
                Node* newNode = new Node();
                newNode->address = freedAddress;
                newNode->len = size;
                newNode->next = NULL;
                currNode->next = newNode;
                break;
            }
            if (freedAddress > currNode->address && freedAddress < currNode->next->address)
            {
                // add new node in between two nodes
                Node *newNode = new Node();
                newNode->address = freedAddress;
                newNode->len = size;
                newNode->next = currNode->next;
                currNode->next = newNode;
                
                // break after inserting element
                break;
            }
            currNode = currNode->next;
        }
    }

  
  // after inserting a free block, merge any blocks that are next to each other
  cout << "\nBEFORE MERGE" << endl;
  printList();

  afterFree(); // this is where the merge happens
  
  cout << "\nAFTER MERGE" << endl;
  printList();

}

FreeList::~FreeList(){
  Node* currNode = head;
  Node* next;

  while (currNode != NULL) {
      next = currNode->next;
      delete currNode;
      currNode = next;
  }
}
