#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <mpi.h>
#include <time.h> 

#define DATA_SIZE 8
#define HOT       0

typedef struct {
    double data[DATA_SIZE];
} data_t;

// Comparison function for qsort
int compare(const void *a, const void *b) {
    const data_t *da = (const data_t *)a;
    const data_t *db = (const data_t *)b;
    return (da->data[HOT] > db->data[HOT]) - (da->data[HOT] < db->data[HOT]);
}

// Partitioning function for quicksort
int partition(data_t *arr, int low, int high) {
    data_t pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (compare(&arr[j], &pivot) < 0) {
            i++;
            data_t temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    data_t temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// Quicksort function
void quicksort(data_t *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Function for parallel merge sort
void parallel_merge(data_t *merged_data, int size, int N, int DATA_SIZE) {
    // Implement parallel merge operation here
    // Each process merges its portion of sorted data
    // Then merge the merged_data arrays using a parallel merge algorithm
}

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time, end_time;

  int N = size * 100000; // Default data size
  if (argc > 1)
      N = atoi(argv[1]) * 100000; // increasing data size

    data_t *data = NULL;
    if (rank == 0) {
        // Generate random data on root process
        data = (data_t *)malloc(N * sizeof(data_t));
        srand(time(NULL));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < DATA_SIZE; j++) {
                data[i].data[j] = (double)rand() / RAND_MAX;
            }
        }
    }

    start_time = MPI_Wtime();

    // Broadcast data size to all processes
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter data to all processes
    data_t *local_data = (data_t *)malloc(N / size * sizeof(data_t));
    MPI_Scatter(data, N / size * DATA_SIZE, MPI_DOUBLE, local_data,
                N / size * DATA_SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Sort local data
    quicksort(local_data, 0, N / size - 1);

    // Gather sorted data back to root process
    data_t *sorted_data = (data_t *)malloc(N * sizeof(data_t));
    MPI_Gather(local_data, N / size * DATA_SIZE, MPI_DOUBLE, sorted_data,
               N / size * DATA_SIZE, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Allocate memory for merged data on root process
        data_t *merged_data = (data_t *)malloc(N * sizeof(data_t));
        // Perform parallel merge sort to merge sorted arrays
        parallel_merge(merged_data, size, N, DATA_SIZE);
        end_time = MPI_Wtime();
        printf("Execution time: %f seconds\n", end_time - start_time);
        free(merged_data);
    }

    // Free allocated memory
    free(local_data);
    if (rank == 0)
        free(data);

    MPI_Finalize();

    return 0;
}
