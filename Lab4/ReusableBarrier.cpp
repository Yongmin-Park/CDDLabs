#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>

// Reusable Barrier

int count = 0;
int numberOfThreads = 3;
bool barrierCondition = false;

using namespace std;

void taskLoop (shared_ptr<Semaphore> mutex, shared_ptr<Semaphore> turnstile1, 
    shared_ptr<Semaphore> turnstile2) {
    
    barrierCondition = true;

    while (barrierCondition) {
        
        mutex->Wait();
        count += 1;

        cout << "Thread count before: " << count << endl;

        if (count == numberOfThreads) {
            turnstile2->Wait();
            turnstile1->Signal();
        }

        mutex->Signal();

        turnstile1->Wait();
        turnstile1->Signal();

        //critial point

        mutex->Wait();
        count -= 1;
        
        if (count <= 0) {   
            turnstile1->Wait();
            turnstile2->Signal();
            barrierCondition = false;
        }

        cout << "Thread count after: " << count + 1 << endl;


        mutex->Signal();

        turnstile2->Wait();
        turnstile2->Signal();
    }
}

int main (void) {

    vector<thread> threadList(numberOfThreads);
    
    shared_ptr<Semaphore> mutex(new Semaphore(1));
    shared_ptr<Semaphore> turnstile1(new Semaphore(0));
    shared_ptr<Semaphore> turnstile2(new Semaphore(1));
    
    /* Launch the threads */
    for (int i = 0;i < threadList.size();i++) {
        threadList[i] = thread(taskLoop, mutex, turnstile1, turnstile2);
    }

    cout << "Launched from the main" << endl;

    for (int i = 0;i < threadList.size();i++) {
        threadList[i].join();
    }
    
    return 0;
}
