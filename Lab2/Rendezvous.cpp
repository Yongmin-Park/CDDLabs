#include "Semaphore.h"
#include <iostream>
#include <thread>

//Rendezvous pattern with two thread A and B
/* we want to guarantee that a1 happens before b2 and b1 happens before a2. */

void taskA(std::shared_ptr<Semaphore> aArrived, std::shared_ptr<Semaphore> bArrived) {
    std::cout << "a1: I am " << std::endl;
    std::cout << "a1: the first " << std::endl;
    std::cout << "a1: statement of " << std::endl;
    std::cout << "a1: thread A" << std::endl;
    std::cout << "" << std::endl;
    
    aArrived->Signal();
    bArrived->Wait();
    
    std::cout << "a2: This " << std::endl;
    std::cout << "a2: should " << std::endl;
    std::cout << "a2: appear " << std::endl;
    std::cout << "a2: later than b1" <<std::endl;
    std::cout << "" << std::endl;
}

void taskB(std::shared_ptr<Semaphore> aArrived, std::shared_ptr<Semaphore> bArrived) {
    std::cout << "b1: I am " << std::endl;
    std::cout << "b1: the first" << std::endl;
    std::cout << "b1: statement of" << std::endl;
    std::cout << "b1: thread B" << std::endl;
    std::cout << "" << std::endl;
    
    bArrived->Signal();
    aArrived->Wait();
    
    std::cout << "b2: This " << std::endl;
    std::cout << "b2: should " << std::endl;
    std::cout << "b2: appear " << std::endl;
    std::cout << "b2: later than a1" << std::endl;
    std::cout << "" << std::endl;
}

int main(void) {
    std::thread threadA, threadB;
    std::shared_ptr<Semaphore> aArrived( new Semaphore);
    std::shared_ptr<Semaphore> bArrived( new Semaphore);
    /* Launch the threads  */
    threadA=std::thread(taskA, aArrived, bArrived);
    threadB=std::thread(taskB, aArrived, bArrived);
    std::cout << "Launched from the main\n";
    threadA.join();
    threadB.join();
    
    return 0;
}
