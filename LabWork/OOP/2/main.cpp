//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <cmath>

using namespace std;

// typedef list
typedef double T1;
typedef int T2;
typedef long T3;

T1* calculateExpr(T2 *p2, T3 *p3)
{
    return new T1(tan(pow(*p2, 2)) * (*p3 / 3.0));
} // func calculateExpr -> T1

int main(int argc, const char * argv[])
{
    T2 valueT2 = 0;
    T3 valueT3 = 0;

    cout << "Write first parametr : ";
    cin >> valueT2;
    
    cout << "Write second parametr : ";
    cin >> valueT3;

    T2 *p2 = &valueT2;
    T3 *p3 = &valueT3;
    
    T1 *result = calculateExpr(p2, p3);
    
    cout << endl << "result calculate : " << *result << endl;
    cout << "value p2 : " << *p2 << endl;
    cout << "address p2 : " << p2 << endl;
    cout << "value valueT2 : " << valueT2 << endl;
    cout << "address valueT2 : " << &valueT2 << endl;

    delete(result);

    return 0;
} // func main
