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
    // example for use sysctlbyname (Device name)
    size_t lenForGPU = 0;
    sysctlbyname("hw.model", NULL, &lenForGPU, NULL, 0);
    char* gpuInfo = new char[lenForGPU];
    sysctlbyname("hw.model", gpuInfo, &lenForGPU, NULL, 0);
    cout << "Device name : \t" << gpuInfo << endl;
    delete[] gpuInfo;
    
    // example for use sysctlbyname (CPU)
    size_t lenForCPU = 0;
    sysctlbyname("machdep.cpu.brand_string", NULL, &lenForCPU, NULL, 0);
    char* cpuInfo = new char[lenForCPU];
    sysctlbyname("machdep.cpu.brand_string", cpuInfo, &lenForCPU, NULL, 0);
    cout << "Processor : " << cpuInfo << endl;
    delete[] cpuInfo;
    
    // example for use popen in sysctlbyname (GPU)
    FILE* gpuPipe = popen("system_profiler SPDisplaysDataType | grep Chip", "r");
    if (gpuPipe)
    {
        char buffer[128];
        string gpuInfo = "";
        while (!feof(gpuPipe))
        {
            if (fgets(buffer, 128, gpuPipe) != nullptr)
                gpuInfo += buffer;
        }
        pclose(gpuPipe);

        cout << "GPU : \t" << gpuInfo;
    }
    
    // print type display
    FILE* resolutionPipe = popen("system_profiler SPDisplaysDataType | grep Resolution", "r");
    if (resolutionPipe)
    {
        char buffer[128];
        string resolutionInfo = "";
        while (!feof(resolutionPipe))
        {
            if (fgets(buffer, 128, resolutionPipe) != nullptr)
                resolutionInfo += buffer;
        }
        pclose(resolutionPipe);

        cout << "Monitor : " << resolutionInfo;

    }
    
    // get RAM information
    int mib[2];
    size_t len;
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    len = sizeof(uint64_t);

    uint64_t totalMemory;
    if (sysctl(mib, 2, &totalMemory, &len, NULL, 0) == 0)
    {
        cout << "Total RAM : " << totalMemory / (1024 * 1024) << " MB" << endl;
    }
    else
    {
        cerr << "Error getting RAM information." << endl;
    }
}// func void printSystemInfo()

// MARK: - Main

int main()
{
    printSystemInfo();
    
    return 0;
}// func int main()
