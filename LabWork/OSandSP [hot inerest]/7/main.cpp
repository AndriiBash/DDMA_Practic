//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cmath>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>
#include <stdexcept>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUF_SIZE 256
#define SHARED_MEM_NAME "/MySharedMemory"

#define PAGE_SIZE sysconf(_SC_PAGESIZE)
#define ROUND_UP_SIZE(size) (((size) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))

#define hStart 0
#define hEnd   10
#define hA     0.5
#define NUM_THREADS 5

using namespace std;
namespace fs = std::filesystem;

mutex outputMutex;
condition_variable cv;

// function for copy in buffer
void writeToClipboard(const string& content)
{
    try
    {
        ostringstream command;
        command << "echo \"" << content << "\" | /usr/bin/pbcopy";
        
        if (system(command.str().c_str()) == -1)
        {
            throw runtime_error("Failed to call pbcopy");
        }
    }
    catch (const exception& error)
    {
        cerr << "Error : " << error.what() << endl;
    }
}// void writeToClipboard(const string& content)

void writeToFile(const string& content, const string& filePath)
{
    ofstream file(filePath);
    if (file.is_open())
    {
        file << content;
        file.close();
    }
    else
    {
        cerr << "Error opening the file for writing." << endl;
    }
}

string readFromFile(const string& filePath)
{
    ifstream file(filePath);
    stringstream buffer;
    
    if (file.is_open())
    {
        buffer << file.rdbuf();
        file.close();
    }
    else
    {
        cerr << "Error opening the file for reading." << endl;
    }
    
    return buffer.str();
}// string readFromFile(const string& filePath)

// Function that represents the work done by each child thread
void threadCalculation(int start, int end, int threadNum, double *pBuf)
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
        
        pBuf[i] = static_cast<double>(sqrt(0.5 * pow(i, 3)));

        this_thread::sleep_for(chrono::milliseconds(200));
    }

    cout << "Neighbor child thread [" << threadNum << "] finished." << endl;
}// void threadCalculation(int start, int end, int threadNum, double *pBuf)

int main()
{
    int fd;
    double *pBuf;

    // Create or open the shared memory object
    fd = shm_open(SHARED_MEM_NAME, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("shm_open");
        return 1;
    }

    // Set the size of the shared memory object
    size_t roundedSize = ROUND_UP_SIZE(BUF_SIZE * sizeof(double));
    
    if (ftruncate(fd, roundedSize) == -1)
    {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    // Map the shared memory into the address space of the process
    pBuf = (double *)mmap(NULL, roundedSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (pBuf == MAP_FAILED)
    {
        perror("mmap");
        close(fd);
        return 1;
    }

    cout << "ID main thread : " << this_thread::get_id() << endl;

    vector<thread> threads;
    int range = (hEnd - hStart) / NUM_THREADS;

    // Create child threads, each responsible for a specific range of values
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int start = hStart + i * range;
        int end = (i == NUM_THREADS - 1) ? hEnd : start + range;
        
        threads.emplace_back(threadCalculation, start, end, i + 1, pBuf);
    }

    this_thread::sleep_for(chrono::milliseconds(200));

    cv.notify_all();  // Send signal for start

    // Wait for all child threads to finish
    for (auto &th : threads)
    {
        th.join();
    }

    // Print the content of shared memory
    cout << endl << "Y values ​​communicated by [" << NUM_THREADS << "] threads : ";
    for (int i = 0; i < BUF_SIZE; ++i)
    {
        if (pBuf[i] != 0)
        {
            cout << static_cast<double>(pBuf[i]) << " ";
        }
    }
    cout << endl;

    // Write results to a file on the desktop
    string filePath = fs::path(getenv("HOME")) / "Desktop" / "results.txt";
    string content;
    
    for (int i = 0; i < BUF_SIZE; ++i)
    {
        if (pBuf[i] != 0)
        {
            content += to_string(static_cast<double>(pBuf[i])) + " ";
        }
    }
    
    writeToFile(content, filePath);

    // Read contents from the file on the desktop
    string fileContent = readFromFile(filePath);
    cout << "File content read from desktop file: " << fileContent << endl;

    // Write answer in buffer clipboard
    writeToClipboard(fileContent);

    // Unmap and close the shared memory object
    if (munmap(pBuf, roundedSize) == -1)
    {
        perror("munmap");
    }

    close(fd);
    shm_unlink(SHARED_MEM_NAME);

    return 0;
}
