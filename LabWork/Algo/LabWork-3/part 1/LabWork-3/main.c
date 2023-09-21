//
//  main.c
//  LabWork-3
//
//  Created by Андрiй on 21.09.2023.
//

#include <stdio.h>
#include <math.h>

int main(void)
{
    float y = 0;
    float a = 6.3;
    float hStart = 2.5; // стартове значення
    float hEnd = 7.5;   // кінцеве значення
    float hStep = 0.5;  // крок з яким виконується цикл
    
    while(hStart <= hEnd)
    {
        if (hStart <= a)
        {
            y = (a * log(hStart))/hStart + pow(hStart,2);
        }
        else
        {
            y = sqrt(a * pow(hStart,2) + sin(hStart));
        }
        
        printf("%.3f\n",y);
        
        hStart += hStep;
    }
    
    return 0;
}
