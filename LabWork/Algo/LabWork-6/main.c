#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x[25];
    int array[25];
    int count = 0;
    
    printf("Маємо такий масив : ");
    
    for(int i = 0; i < sizeof(x)/sizeof(x[0]); i++)
    {
        x[i] = rand()% 25 - 10;
        
        if (x[i] % 2 != 0)
        {
            array[count] = x[i];
            count++;
        }
        
        printf(" %d ", x[i]);
    }
 
    printf("\nМаємо такий масив з непарних елементів : ");
    
    for(int i = 0; i < count; i++)
    {
        printf(" %d ", array[i]);
    }
    
    printf("\n");

    return 0;
}
