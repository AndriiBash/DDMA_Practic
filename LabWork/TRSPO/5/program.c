#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int my_rank, num_procs, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    // Ініціалізація MPI
    MPI_Init(&argc, &argv);

    // Отримання кількості процесів
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // Отримання номера поточного процесу
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Отримання назви вузла (ім'я комп'ютера)
    MPI_Get_processor_name(processor_name, &name_len);

    // Виведення інформації про кожен процес
    printf("Процес #%d з %d виконується на вузлі: %s\n", my_rank, num_procs, processor_name);

    // Виведення додаткової інформації для K-го і M-го процесів
    if (my_rank == 0) {  // K = 0
        printf("Процес #%d: Прізвище - Ізбаш\n", my_rank);
    }

    if (my_rank == 2) {  // M = 2
        printf("Процес #%d: Ім'я - Андрій\n", my_rank);
    }

    // Завершення роботи MPI
    MPI_Finalize();
    return 0;
}
