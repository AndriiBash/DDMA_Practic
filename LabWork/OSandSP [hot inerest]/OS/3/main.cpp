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

#define hStart 0
#define hEnd   10
#define hA     0.5
#define NUM_THREADS 5

using namespace std;

mutex outputMutex;
condition_variable cv;
bool neighborsFinished = false;

void threadCalculation(int start, int end, int threadNum)
{
    unique_lock<std::mutex> lock(outputMutex);
    cv.wait(lock);  // wait signal

    cout << "ID Child thread " << threadNum << " : " << std::this_thread::get_id() << std::endl;

    this_thread::sleep_for(chrono::milliseconds(200));

    static bool neighborsFinished = false;
    if (!neighborsFinished)
    {
        cout << "\t x \t y " << std::endl;
        neighborsFinished = true;
    }

    for (int i = start; i < end; i++)
    {
        cout << "\t " << i << "\t " << sqrt(hA * pow(i, 3)) << std::endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    cout << "Neighbor child thread [" << threadNum << "] finished." << endl;
}

int main(int argc, const char *argv[])
{
    cout << "ID MainThread : " << this_thread::get_id() << endl;

    vector<thread> threads;
    int range = (hEnd - hStart) / NUM_THREADS;

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int start = hStart + i * range;
        int end = (i == NUM_THREADS - 1) ? hEnd : start + range;

        threads.emplace_back(threadCalculation, start, end, i + 1);
    }

    this_thread::sleep_for(chrono::milliseconds(200));

    cv.notify_all();  // Send signal for start

    for (auto &th : threads)
    {
        th.join();
    }

    return 0;
}
