#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    // Ініціалізація MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    // Отримуємо унікальний номер (ранг) поточного процесу
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    // Дізнаємось загальну кількість процесів у програмі
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Перевіряємо, чи запущено достатню кількість процесів (мінімум 6)
    if (size < 6) {
        if (rank == 0) { // Повідомлення виводиться лише в процесі 0, щоб уникнути дублювання
            printf("Потрібно запустити щонайменше 6 процесів!\n");
        }
        MPI_Finalize(); // Завершуємо виконання MPI
        return 1;
    }

    // --- Відправлення та прийом даних між процесами ---

    // Процес 3 відправляє процесу 5 значення 7.875 (double)
    if (rank == 3) {
        double value = 7.875;
        MPI_Send(&value, 1, MPI_DOUBLE, 5, 0, MPI_COMM_WORLD);
        printf("Процес 3 відправив процесу 5: %lf\n", value);
    }

    // Процес 5 приймає дані від 3 і далі передає повідомлення процесам 2 і 3
    if (rank == 5) {
        // Отримання від 3 -> 5: 7.875
        double received_value;
        MPI_Status status;
        MPI_Recv(&received_value, 1, MPI_DOUBLE, 3, 0, MPI_COMM_WORLD, &status);
        printf("Процес 5 отримав від процесу %d: %lf\n", status.MPI_SOURCE, received_value);

        // --- Передача даних до процесу 2 ---
        int int_value = 87;
        char message[] = "Кожній принцесі покладено кат.";
        MPI_Ssend(&int_value, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
        MPI_Ssend(message, strlen(message) + 1, MPI_CHAR, 2, 2, MPI_COMM_WORLD);
        printf("Процес 5 відправив процесу 2: %d, \"%s\"\n", int_value, message);

        // --- Передача даних до процесу 3 ---
        int another_value = 5;
        MPI_Ssend(&another_value, 1, MPI_INT, 3, 3, MPI_COMM_WORLD);
        printf("Процес 5 відправив процесу 3: %d\n", another_value);
    }

    // Процес 2 приймає дані від процесу 5
    if (rank == 2) {
        int received_int;
        char received_message[100];
        MPI_Status status;
        MPI_Recv(&received_int, 1, MPI_INT, 5, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(received_message, 100, MPI_CHAR, 5, 2, MPI_COMM_WORLD, &status);
        printf("Процес 2 отримав від процесу %d: %d, \"%s\"\n", status.MPI_SOURCE, received_int, received_message);
    }

    // Процес 3 приймає ще одне число від процесу 5
    if (rank == 3) {
        int received_value;
        MPI_Status status;
        MPI_Recv(&received_value, 1, MPI_INT, 5, 3, MPI_COMM_WORLD, &status);
        printf("Процес 3 отримав від процесу %d: %d\n", status.MPI_SOURCE, received_value);
    }

    // Завершення роботи MPI
    MPI_Finalize();
    return 0;
}
