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
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 256
#define SHARED_MEM_NAME "/MySharedMemory"

using namespace std;

mutex outputMutex;
condition_variable cv;

// Function that represents the work done by each child thread
void threadCalculation(int start, int end, int threadNum, char *pBuf)
{
    unique_lock<mutex> lock(outputMutex);
    cv.wait(lock);  // wait signal

    cout << "ID Child thread " << threadNum << " : " << this_thread::get_id() << endl;

    this_thread::sleep_for(chrono::milliseconds(200));

    static bool neighborsFinished = false;
    if (!neighborsFinished)
    {
        cout << "\t x \t y " << endl;
        neighborsFinished = true;
    }

    for (int i = start; i < end; i++)
    {
        cout << "\t " << i << "\t " << sqrt(0.5 * pow(i, 3)) << endl;
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    cout << "Neighbor child thread [" << threadNum << "] finished." << endl;
}

int main()
{
    int fd;
    char *pBuf;

    // Create or open the shared memory object
    fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("shm_open");
        return 1;
    }

    // Set the size of the shared memory object
    if (ftruncate(fd, BUF_SIZE) == -1)
    {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    // Map the shared memory into the address space of the process
    pBuf = (char *)mmap(NULL, BUF_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (pBuf == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    cout << "ID main thread : " << this_thread::get_id() << endl;

    vector<thread> threads;
    int range = (10 - 0) / 5;

    // Create child threads, each responsible for a specific range of values
    for (int i = 0; i < 5; ++i)
    {
        int start = 0 + i * range;
        int end = (i == 5 - 1) ? 10 : start + range;

        threads.emplace_back(threadCalculation, start, end, i + 1, pBuf);
    }

    this_thread::sleep_for(chrono::milliseconds(200));

    cv.notify_all();  // Send signal for start

    // Wait for all child threads to finish
    for (auto &th : threads)
    {
        th.join();
    }

    // Unmap and close the shared memory object
    if (munmap(pBuf, BUF_SIZE) == -1)
    {
        perror("munmap");
    }

    close(fd);
    shm_unlink(SHARED_MEM_NAME);

    return 0;
}
