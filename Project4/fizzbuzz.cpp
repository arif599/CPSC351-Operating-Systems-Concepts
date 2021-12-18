#include<unistd.h>
#include<iostream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<vector> 
#include<cassert>

#include "pthread-wrappers.h" 


using namespace std; 

//To compile, include -lpthread


int *buffer; 
Cond empty, filled;
Mutex m; 
//int max;
int loops; 
int consumers; 

int fill_ptr = 0;
int use_ptr = 0; 
int num_full = 0; 


// Producer fills buffer with data
void do_fill(int value){

    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % loops; 
    num_full++; 

}

// Consumer gets data from buffer
int do_get(){
    int i = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % loops;
    num_full--; 
    return i; 
}

//Call do_fill() in the critical section to fill buffer
void * producer(void *){
    for(int i = 1; i <= loops; i++){
        m.lock();
        while(num_full == loops)
            empty.wait(m);
        do_fill(i);
        empty.signal();
        m.unlock();
    }
    
}

//Consume contents of buffer and display correct output
void * consumer(void *){

    for(int i = 1; i <= loops; i++){
        m.lock();
        while(num_full == 0){
            empty.wait(m);
            }

        int tmp = do_get();
        empty.signal();

        if(tmp % 3 == 0 && tmp % 5 == 0){
          cout << "fizzbuzz\n"; }
      
        else if(tmp % 3 == 0) {
          cout << "fizz\n"; }
        
        else if(tmp % 5 == 0) {
          cout << "buzz\n";}

        else{
          cout << tmp << endl; }
         
        
        m.unlock(); 
    }
}



int main(int argc, char *argv[]){

    loops = atoi(argv[1]);
    
    
    Thread pid,pid1, cid;
    
    buffer = (int * )malloc(loops * sizeof(int));
    assert(buffer != NULL);

    pid.create(producer);
    cid.create(consumer);
    pid.join();
    cid.join();

    return 0; 
}
