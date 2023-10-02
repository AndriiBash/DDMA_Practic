#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int arraySize = 0;
    int sum = 0;
    
    printf("Введіть розмір масиву: ");
    scanf("%d", &arraySize);
    
    int array[arraySize];
    
    printf("Маємо такий масив: ");
    for(int i = 0; i < arraySize; i++)
    {
        array[i] = rand() % 45;
        printf(" %d ", array[i]);
        
        if (array[i] % 3 == 0)
        {
            sum += array[i];
        }
    }
    
    printf("\nСума кратних 3 елементів : %d\n", sum);

    return 0;
}
