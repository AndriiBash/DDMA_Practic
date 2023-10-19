#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int matrix[5][5];
    int sum = 0;
    int count = 0;
    
    printf("Маємо таку матрицю: \n");
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matrix[i][j] = rand() % 25 - 10;
            
            if (j == 3 && matrix[i][j] % 3 == 0)
            {
                sum += matrix[i][j];
            }
            else if (i == 1 && matrix[i][j] % 2 != 0)
            {
                count++;
            }
            
            printf("  %2d  ", matrix[i][j]);
        }
        printf("\n");
    }
     
    printf("\nCума кратних 3 чисел у 4-му стовпці : %3d", sum);
    printf("\nКількість непарних чисел 2-го рядка матриці : %3d", count);
    printf("\nЇх добуток : %3d\n", sum * count);
    
    return 0;
}

