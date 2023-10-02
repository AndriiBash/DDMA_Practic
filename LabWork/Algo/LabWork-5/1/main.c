#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void)
{
    int arraySize = 0;
    int count = 0;
    
    printf("Введіть розмір масиву: ");
    scanf("%d", &arraySize);
    
    int array[arraySize];
    
    printf("Маємо такий масив: ");
    for(int i = 0; i < arraySize; i++)
    {
        array[i] = rand() % 45;
        printf(" %d ", array[i]);
        
        if (array[i] % 2 == 0)
        {
            count++;
        }
    }
    
    printf("\nКількість парних елементів : %d\n", count);

    return 0;
}
