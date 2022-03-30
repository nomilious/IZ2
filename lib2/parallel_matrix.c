#include "parallel_matrix.h"

int *solve_hard(int *array, int rows, int cols) {
    int max_proc = sysconf(_SC_NPROCESSORS_ONLN);
    int *shared_i = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int *new_arr = mmap(NULL, rows * cols * sizeof(int), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_i == MAP_FAILED || new_arr == MAP_FAILED)
        return NULL;

    *shared_i = -1;
    for (int k = 0; k < max_proc && *shared_i < rows; ++k) {
        int pid = fork();
        if (!pid) {
            for (int nr = ++(*shared_i); nr < cols;) {
                for (int j = 0; j < rows; ++j)
                    new_arr[nr * rows + j] = array[(rows - 1 - j) * cols + (cols - 1 - nr)];
                nr = ++(*shared_i);
            }
            exit(0);
        }
    }

    return new_arr;
}