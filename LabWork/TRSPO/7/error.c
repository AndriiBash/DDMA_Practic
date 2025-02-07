#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Ініціалізація MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Отримання рангу процесу
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Отримання кількості процесів

    if (size < 6) {
        if (rank == 0) {
            printf("Потрібно запустити щонайменше 6 процесів!\n");
        }
        MPI_Finalize();
        return 1;
    }

    // Тупикова ситуація: процес 3 чекає на процес 5, а процес 5 чекає на процес 3
    if (rank == 3) {
        double value = 7.875;
        MPI_Send(&value, 1, MPI_DOUBLE, 5, 0, MPI_COMM_WORLD);
        printf("Процес 3 відправив процесу 5: %lf\n", value);
        
        // Тупикова ситуація: чекаємо повідомлення від процесу 5
        double received_value;
        MPI_Recv(&received_value, 1, MPI_DOUBLE, 5, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Процес 3 отримав від процесу 5: %lf\n", received_value);
    }

    if (rank == 5) {
        // Отримуємо значення від процесу 3
        double received_value;
        MPI_Recv(&received_value, 1, MPI_DOUBLE, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Процес 5 отримав від процесу 3: %lf\n", received_value);

        // 5 -> 2: 87, "Кожній принцесі покладено кат."
        int int_value = 87;
        char message[] = "Кожній принцесі покладено кат.";
        MPI_Send(&int_value, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 2, 2, MPI_COMM_WORLD);
        printf("Процес 5 відправив процесу 2: %d, \"%s\"\n", int_value, message);

        // 5 -> 3: 5
        int another_value = 5;
        MPI_Send(&another_value, 1, MPI_INT, 3, 3, MPI_COMM_WORLD);
        printf("Процес 5 відправив процесу 3: %d\n", another_value);

        // Тупикова ситуація: чекаємо на повідомлення від процесу 3
        double another_received_value;
        MPI_Recv(&another_received_value, 1, MPI_DOUBLE, 3, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Процес 5 отримав від процесу 3: %lf\n", another_received_value);
    }

    // Логіка нормальної роботи, щоб уникнути тупикової ситуації
    if (rank == 3) {
        double value = 7.875;
        MPI_Send(&value, 1, MPI_DOUBLE, 5, 0, MPI_COMM_WORLD);
        printf("Процес 3 відправив процесу 5: %lf\n", value);

        // Відправляємо значення 5 процесу 5 і отримуємо від нього 87
        int int_value = 5;
        MPI_Send(&int_value, 1, MPI_INT, 5, 3, MPI_COMM_WORLD);

        // Тепер очікуємо результат
        double received_value;
        MPI_Recv(&received_value, 1, MPI_DOUBLE, 5, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Процес 3 отримав від процесу 5: %lf\n", received_value);
    }

    if (rank == 5) {
        // Отримуємо повідомлення від процесу 3
        double received_value;
        MPI_Recv(&received_value, 1, MPI_DOUBLE, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Процес 5 отримав від процесу 3: %lf\n", received_value);

        // 5 -> 2: 87, "Кожній принцесі покладено кат."
        int int_value = 87;
        char message[] = "Кожній принцесі покладено кат.";
        MPI_Send(&int_value, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 2, 2, MPI_COMM_WORLD);
        printf("Процес 5 відправив процесу 2: %d, \"%s\"\n", int_value, message);

        // 5 -> 3: 5
        int another_value = 5;
        MPI_Send(&another_value, 1, MPI_INT, 3, 3, MPI_COMM_WORLD);
        printf("Процес 5 відправив процесу 3: %d\n", another_value);
    }

    MPI_Finalize(); // Завершення роботи MPI
    return 0;
}


