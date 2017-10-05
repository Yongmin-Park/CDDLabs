#include "Semaphore.h"
#include <iostream>
#include <thread>

// Mutual exclusion

void taskA (std::shared_ptr<Semaphore> mutex, int *count) {
    mutex->Wait();

    // critical section
    *count = *count + 1;

    mutex->Signal();
}

void taskB (std::shared_ptr<Semaphore> mutex, int *count) {
    mutex->Wait();

    // critical section
    *count = *count + 1;

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
