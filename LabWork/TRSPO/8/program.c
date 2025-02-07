#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ROOT 0
#define N 15000  // Розмір масиву

char *mas;      // Глобальний масив
double time0, time1;  // Змінні для вимірювання часу виконання
int myrank, p;  // Номер поточного процесу та загальна кількість процесів

// Функція ініціалізації масиву (виконується тільки у головному процесі)
void MStart() {
    int i;
    mas = (char*)malloc(N * sizeof(char));  // Виділення пам'яті під масив
    srand(1);  // Ініціалізація генератора випадкових чисел

    // Виведення інформації про кількість процесів
    printf("%d процес%s.\nМасив:\n", p, (p % 10 == 1 && p % 100 != 11) ? "" : "ів");

    // Заповнення масиву випадковими символами з діапазону [A-Z]
    for (i = 0; i < N; i++) 
        mas[i] = 'A' + (rand() % 26);

    // Виведення перших 10 елементів
    for (i = 0; i < 10; i++) 
        printf("M[%d]=%c ", i, mas[i]);
    
    printf("... ");  // Позначення пропущених елементів
    
    // Виведення останніх 10 елементів
    for (i = N - 10; i < N; i++) 
        printf("M[%d]=%c ", i, mas[i]);
    
    printf("\n");

    time0 = MPI_Wtime();  // Початок вимірювання часу
}

// Функція завершення (тільки у головному процесі)
void MFinish() {
    int i;
    time1 = MPI_Wtime();  // Кінець вимірювання часу

    // Виведення часу виконання
    printf("\nВиконано за %lf секунд.\nНовий масив:\n", time1 - time0);

    // Виведення перших 10 елементів
    for (i = 0; i < 10; i++) 
        printf("M[%d]=%c ", i, mas[i]);
    
    printf("... ");
    
    // Виведення останніх 10 елементів
    for (i = N - 10; i < N; i++) 
        printf("M[%d]=%c ", i, mas[i]);

    printf("\n");

    free(mas);  // Звільнення пам'яті
}

// Головна функція
int main(int argc, char **argv) {
    int i, j;
    char k, prev, next;
    MPI_Status Status;

    MPI_Init(&argc, &argv);  // Ініціалізація MPI
    MPI_Comm_size(MPI_COMM_WORLD, &p);  // Отримання кількості процесів
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);  // Отримання рангу (ідентифікатора) поточного процесу

    if (myrank == ROOT) 
        MStart();  // Ініціалізація масиву у головному процесі

    // Розмір частини масиву для кожного процесу
    int bsize = N / p;
    char *buf = (char*)malloc((bsize + 1) * sizeof(char));  // Буфер для зберігання частини масиву

    // Розсилка масиву всім процесам
    MPI_Scatter(mas, bsize, MPI_CHAR, buf, bsize, MPI_CHAR, ROOT, MPI_COMM_WORLD);

    next = myrank + 1;  // Наступний процес
    prev = myrank - 1;  // Попередній процес

    // Алгоритм чет-непарного сортування (Odd-Even Sort)
    for (j = 0; j < N; j++) {
        // Парний прохід: обмін значеннями між сусідніми парними індексами
        for (i = 0; i <= bsize - 2; i += 2) {
            if (buf[i] > buf[i + 1]) {
                k = buf[i];
                buf[i] = buf[i + 1];
                buf[i + 1] = k;
            }
        }

        // Передача граничних значень між процесами
        if (prev >= 0) 
            MPI_Send(&buf[0], 1, MPI_CHAR, prev, 1, MPI_COMM_WORLD);
        if (next < p) 
            MPI_Recv(&buf[bsize], 1, MPI_CHAR, next, 1, MPI_COMM_WORLD, &Status);

        // Непарний прохід: обмін значеннями між сусідніми непарними індексами
        for (i = 1; i <= bsize - 2; i += 2) {
            if (buf[i] > buf[i + 1]) {
                k = buf[i];
                buf[i] = buf[i + 1];
                buf[i + 1] = k;
            }
        }

        // Передача граничних значень між процесами
        if (next < p) 
            MPI_Send(&buf[bsize], 1, MPI_CHAR, next, 1, MPI_COMM_WORLD);
        if (prev >= 0) 
            MPI_Recv(&buf[0], 1, MPI_CHAR, prev, 1, MPI_COMM_WORLD, &Status);
    }

    // Збірка частин масиву в один після сортування
    MPI_Gather(buf, bsize, MPI_CHAR, mas, bsize, MPI_CHAR, ROOT, MPI_COMM_WORLD);

    free(buf);  // Звільнення пам'яті

    if (myrank == ROOT) 
        MFinish();  // Виведення результату у головному процесі

    MPI_Finalize();  // Завершення роботи MPI
    return 0;
}
