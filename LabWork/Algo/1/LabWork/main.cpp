//
//  main.cpp
//  LabWork
//
//  Created by Андрiй on 04.09.2023.
//

#include <iostream>
#include <math.h>

using namespace std;

double getNum(string name)
{
    double returnNumber;
    
    cout << "Write value for " + name + ": ";
    cin >> returnNumber;
    
    return returnNumber;
}


int main()
{
    double G;           // your answer
    double x;           // another variables for calculate answer
    double y;           //
    double z;           //
    double c;           //
    
    x = getNum("x");
    y = getNum("y");
    z = getNum("z");
    c = getNum("c");
    
    G = (tan(pow(x,4) - 6) - pow(cos(z + x * y), 3)) / (cos(4) * pow(x,3) * pow(c,2));
    
    cout << "Answer G: " << G << "\n";
    
    return 0;
}
