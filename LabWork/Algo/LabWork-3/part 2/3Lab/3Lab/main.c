//
//  main.c
//  3Lab
//
//  Created by Андрiй on 21.09.2023.
//

#include <stdio.h>
#include <math.h>

int main(void)
{
    float sum = 0;
    float a = 2;
    float b = 7;
    float c = 0.5;
    
    for (float x = a; x <= b; x += c)
    {
        sum += (sqrt(fabsf(x)) + exp(-x)) / (5 * atan(4 * x));
    }
    
    printf("Ваша сума: %f \n", sum);
    
    return 0;
}
