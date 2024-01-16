//
//  main.cpp
//  CommandLineToolC++
//
//  Created by Андрiй on 10.01.2024.
//

#include <iostream>
#include <math.h>

using namespace std;

template <typename type>
type a(type parametr)
{
    return 3 * parametr - 2 * pow(cos(parametr), 2);
} // func a(type parametr) -> type

template <typename type>
type b(type parametr)
{
    return log(parametr) + 2 * exp(parametr);
} // func b(type parametr) -> type

template <typename type>
type c(type parametr)
{
    return pow(parametr, 1/3) + 4 * parametr - 1;
}// func c(type parametr) -> type

template <typename type>
type h(type parametr)
{
    return 3 * a(parametr) + 4 * b(parametr) - 8;
}// func h(type parametr) -> type

int main(int argc, const char * argv[])
{
    const float x = 0.3;
    
    float resultFromH = h(x);
    double resultFromA = a(x);
    double_t resultFromB = b(x);
    float_t resultFromC = c(x);

    cout << "Answer H : " << resultFromH << "\n";
    cout << "Answer A : " << resultFromA << "\n";
    cout << "Answer B : " << resultFromB << "\n";
    cout << "Answer C : " << resultFromC << "\n";

    return 0;
}// int main
