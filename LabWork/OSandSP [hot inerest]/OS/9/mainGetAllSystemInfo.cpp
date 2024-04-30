//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <sys/types.h>
#include <sys/sysctl.h>

using namespace std;

void printSystemInfo()
{
    FILE* allSystemInfo = popen("system_profiler", "r");
    if (allSystemInfo)
    {
        char buffer[128];
        string gpuInfo = "";
        while (!feof(allSystemInfo))
        {
            if (fgets(buffer, 128, allSystemInfo) != nullptr)
                gpuInfo += buffer;
        }
        pclose(allSystemInfo);

        cout << gpuInfo;
    }
}// func void printSystemInfo()

// MARK: - Main

int main()
{
    printSystemInfo();
    
    return 0;
}// func int main()
