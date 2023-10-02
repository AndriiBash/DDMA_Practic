#include <stdio.h>
#include <math.h>

int main(void) {
    
    int x = 0;
    float y = 0;
    
    printf("Введіть значення за яким буде розрахунок [x]: ");
    scanf("%d", &x);
    
    switch (x)
    {
        case 7:         // непарні числа з інтервалу [6,12]
        case 9:
        case 11:
            y = exp(2 * x - 5);
            break;
        case 6:         // парні числа з інтервалу [6,12]
        case 8:
        case 10:
        case 12:
            y = pow(cos(M_PI * x),2);
            break;
        case -2:        // інтервал [-2,5]
        case -1:
        case 0:
        case 1:
        case 2:
        case 4:
        case 5:
            y = log(pow(x,2) + 2.5);
            break;
        default:        // інші числа
            y = asin(x/30);
            break;
    }
    
    printf("y = %3.3f | x = %2d \n", y ,x);
    return 0;
}
