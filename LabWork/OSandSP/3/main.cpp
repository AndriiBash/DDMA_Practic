//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <semaphore.h>

#define hStart 0
#define hEnd   10
#define hA     0.5

using namespace std;

mutex outputMutex;
condition_variable cv;
bool neighborsFinished = false;
vector<string> buffer;
sem_t bufferSemaphore;

void threadCalculation(int start, int end)
{
    unique_lock<mutex> lock(outputMutex, defer_lock);

    cout << "ID Child thread : " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::milliseconds(200));

    lock.lock();
    if (!neighborsFinished)
    {
        buffer.push_back("\t x \t y ");
        neighborsFinished = true;
    }
    lock.unlock();

    for (int i = start; i < end; i++)
    {
        lock.lock();
        cout << "\t " << i << "\t " << sqrt(hA * pow(i, 3)) << endl;
        lock.unlock();

        this_thread::sleep_for(chrono::milliseconds(200));
    }

    lock_guard<mutex> outputLock(outputMutex);
    cout << "Neighbor child thread [" << this_thread::get_id() << "] finished." << endl;

    // Signal the event that the thread has finished
    sem_post(&bufferSemaphore);
}

int main(int argc, const char *argv[])
{
    cout << "ID MainThread : " << this_thread::get_id() << endl;

    int mid = (hEnd + hStart) / 2;

    sem_init(&bufferSemaphore, 0, 0);  // Initialization of the semaphore

    thread firstThread(threadCalculation, hStart, mid);
    thread secondTheard(threadCalculation, mid, hEnd);

    {
        unique_lock<mutex> lock(outputMutex);
        cv.wait(lock, [] { return neighborsFinished; });
    }

    sem_wait(&bufferSemaphore);  // Instead of waiting for an event, we wait for the semaphore

    firstThread.join();
    secondTheard.join();

    sem_destroy(&bufferSemaphore);  // Destroy the semaphore

    return 0;
}
