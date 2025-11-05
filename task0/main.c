#include <mpi.h>
#include <stdio.h>

int proc_count, proc_this;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &proc_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_this);

    printf("Hello I`m processor NO_%d FROM %d\n", proc_this, proc_count);

    MPI_Finalize();
    return 0;
}
