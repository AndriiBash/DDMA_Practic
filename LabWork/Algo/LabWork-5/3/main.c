#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int arraySize = 0;
    int max = 0;
    int min = 0;

    printf("Введіть розмір масиву: ");
    scanf("%d", &arraySize);
    
    int array[arraySize];
    
    printf("Маємо такий масив: ");
    for(int i = 0; i < arraySize; i++)
    {
        array[i] = rand() % 45 - 10;
        
        if (array[i] > max)
        {
            max = array[i];
        }

        if (array[i] < min)
        {
            min = array[i];
        }
        
        printf(" %d ", array[i]);
    }
    
    printf("\nМаксимум: %d\nМінімум: %d\nЇх різність: %d\n", max, min, max - min);
    return 0;
}
