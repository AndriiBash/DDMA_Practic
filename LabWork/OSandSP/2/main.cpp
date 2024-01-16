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


#define hStart 0
#define hEnd   10
#define hA     0.5


using namespace std;

mutex outputMutex;
condition_variable cv;
atomic<bool> printed(false);

bool neighborsFinished = false;


void threadCalculation(int start, int end)
{
    unique_lock<mutex> lock(outputMutex, defer_lock);

    cout << "ID Child thread : " << this_thread::get_id() << endl;
    this_thread::sleep_for(chrono::milliseconds(200)); // for wait all thread xD

    lock.lock();
    if (!printed)
    {
        cout << "\t x \t y " << endl;
        printed = true;
    }
    lock.unlock();
    
  
    for (int i = start; i < end; i++)
    {
        lock.lock();
        cout << "\t " << i << "\t " << sqrt(hA * pow(i, 3)) << endl;
        lock.unlock();

        this_thread::sleep_for(chrono::milliseconds(200));
    }
    
    
    {
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << "Neighbor child thread [" << this_thread::get_id() << "] finished." << std::endl;
        neighborsFinished = true;
    }
    
    cv.notify_one(); // end thread msg
}// void threadCalculation(int start, int end)

int main(int argc, const char * argv[])
{
    cout << "ID MainThread : " << this_thread::get_id() << endl;

    // Split the range for each thread
    int mid = (hEnd + hStart) / 2;

    // Create two threads for each half of the range
    thread firstThread(threadCalculation, hStart, mid);
    thread secondTheard(threadCalculation, mid, hEnd);

    // Join threads
    {
        unique_lock<mutex> lock(outputMutex);
        cv.wait(lock, [] { return neighborsFinished; });
    }
    
    // Join threads
    firstThread.join();
    secondTheard.join();
    

    return 0;
}// int main(int argc, const char * argv[])
