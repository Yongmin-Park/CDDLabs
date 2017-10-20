#include "Semaphore.h"
#include <iostream>
#include <thread>

// Mutual exclusion

void taskA (std::shared_ptr<Semaphore> mutex, int *count) {
    mutex->Wait();
    std::cout << "tA: count before: " << *count << std::endl;
    
    // critical section
    *count = *count + 1;

    std::cout << "tA: count after: " << *count << std::endl;
    mutex->Signal();
}

void taskB (std::shared_ptr<Semaphore> mutex, int *count) {
    mutex->Wait();
    std::cout << "tB: count before: " << *count << std::endl;

    // critical section
    *count = *count + 1;

    std::cout << "tB: count after: " << *count << std::endl;
    mutex->Signal();
}

int main (void) {
    int count = 0;

    std::thread threadA, threadB;
    std::shared_ptr<Semaphore> mutex(new Semaphore);

    /* Launch the threads */
    threadA=std::thread(taskA, mutex, &count);
    threadB=std::thread(taskB, mutex, &count);
    std::cout << "Launched from the main\n";

    std::cout << "count before: " << count << std::endl;

    threadA.join();
    threadB.join();
    
    std::cout << "count after: " << count << std::endl;

    return 0;
}
