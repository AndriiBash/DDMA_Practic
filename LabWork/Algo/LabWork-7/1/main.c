#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int matrix[5][5];
    int multiply = 1;
    
    printf("Маємо таку матрицю: \n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matrix[i][j] = rand() % 25 - 10;
            
            if (matrix[i][j] > 0 && matrix[i][j] % 2 == 0)
            {
                multiply *= matrix[i][j];
            }
            
            printf("  %2d  ", matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\nДобуток додатних парних елементів: %d \n", multiply);
 
    return 0;
}

