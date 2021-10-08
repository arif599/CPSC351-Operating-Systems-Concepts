#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <map>
#include <vector>
using namespace std;

const auto KB = 1024;
//Placed in memory right before allocation happens
class headerBlock{
    public:
        size_t size;
        std::byte *blockPtr; 
    public:
        headerBlock(size_t size, std::byte* blockPtr){
            this->size = size;
            this->blockPtr = blockPtr;
        }
};

//Free list implementation 
class Node{
    public:
        std::byte *address;
        size_t len;
        Node *next; 
        Node *prev;
};

class FreeList{
    public:
        Node* head;
        Node* tail;

    public:
        void initialize(std::byte *allocatedHeap, size_t size){
            head = nullptr;
            Node* newNode = new Node();
            newNode->address = allocatedHeap;
            newNode->len = size;
            newNode->next = NULL;
            newNode->prev = NULL;
            head = newNode;
            tail = head;
            

            cout << "\tINITIALIZING FREE LIST:" << endl;
            cout << "\t\tAddress - " << newNode->address << endl;
            cout << "\t\tLength - " << newNode->len << " KB" << endl;
        }
    

        std::byte* firstFit(size_t size){
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
        void printList(){
          Node* currNode = head;
          int i = 0;
            while(currNode != NULL){
              cout << "\nNode " << i << ":\n" << endl;
              cout << "\tAddress - " << currNode->address << endl;
              cout << "\tSize - " << currNode->len << endl;

              cout << "\tAddress + size - " << currNode->address + currNode->len << endl;
              //cout << "\tNext Address - " << currNode->next->address << endl;
              currNode = currNode->next;
              i++;
            }
        }
        void afterFree(){
            // merge any blocks of free spaces
            Node *currNode = head;
            while(currNode != NULL){
              std::byte *sum = currNode->address + currNode->len;
              while(currNode->next != NULL && sum == currNode->next->address){
                  // merge blocks
                  currNode->len += currNode->next->len;
                  if(currNode->next->next != NULL){
                    currNode->next = currNode->next->next;
                  }else{
                    currNode->next = NULL;
                  }
                sum = currNode->address + currNode->len;
              }
              currNode = currNode->next;
            }
        }

        void addFree(std::byte *freedAddress, size_t size){
              // for (unsigned int i = 0; i < size; i++)
              // {
              //     delete freedAddress[i];
              // }

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
                        // adding new node to the end of the linked list
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

          cout << "BEFORE MERGE" << endl;
          printList();
          afterFree();
          cout << "AFTER MERGE" << endl;
          printList();


        }
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

