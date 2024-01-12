//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <thread>

#define hStart 0
#define hEnd   10
#define hA     0.5

using namespace std;

void threadCalculation()
{
    cout << "ID Child thread : " << this_thread::get_id() << endl;
 
    cout << "\t x \t y " << endl;
    for (int i = hStart; i < hEnd; i++)
    {
        cout << "\t " << i << "\t " << sqrt(hA * pow(i, 3)) << endl;
        
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    
    return;
}

int main(int argc, const char * argv[])
{
    cout << "ID MainThread : " << this_thread::get_id() << endl;
    
    // create thread
    thread mainThread(threadCalculation);
    mainThread.join();
    
    return 0;
}
