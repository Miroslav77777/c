#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int proc_this, proc_count;
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_this);
    MPI_Comm_size(MPI_COMM_WORLD, &proc_count);

    int n = 10;
    int a[n];

    // Засекаем время начала
    double start_time = MPI_Wtime();

    // Ввод данных на процессе 0
    if (proc_this == 0) {
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
    }

    // Рассылаем массив всем процессам
    MPI_Bcast(a, n, MPI_INT, 0, MPI_COMM_WORLD);

    // Циклическое распределение: каждый процесс берет элементы через proc_count
    int partial_sum = 0;
    for (int i = proc_this; i < n; i += proc_count) {
        partial_sum += a[i];
    }

    printf("Process %d/%d: partial sum = %d\n", proc_this, proc_count, partial_sum);

    // Собираем общую сумму на процессе 0
    int total_sum = 0;
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Засекаем время окончания
    double end_time = MPI_Wtime();
    double elapsed = end_time - start_time;

    printf("Process %d finished in %f ms\n", proc_this, elapsed);

    // Только процесс 0 выводит общую сумму
    if (proc_this == 0) {
        printf("Total sum = %d\n", total_sum);
    }

    MPI_Finalize();
    return 0;
}