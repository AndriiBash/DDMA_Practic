//
//  main.c
//  LabWork-2
//
//  Created by Андрiй on 08.09.2023.
//

#include <stdio.h>
#include <math.h>

int main(int argc, const char * argv[])
{
    int x = 0;
    int a = 0;
    float y = 0;
    
    printf("Write your value x: ");
    scanf("%d", &x);
    
    printf("Write your value a: ");
    scanf("%d", &a);
        
    if (x <= 0)
    {
        y = 3 * pow(x,5) - 1/(tan(pow(x,3)));
    }
    else if (0 < x && x <= a)
    {
        y = pow(log(sin(4 * x) + 1), 2);
    }
    else
    {
        y = cbrt(2 * pow(x,2) + pow(x,4) + 1);
    }
    
    printf("Answer: %.3f\n", y);               // .3 for round num after 3 nums,

    return 0;
}
