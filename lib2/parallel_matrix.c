#include "parallel_matrix.h"

inline int *solve_hard(const int *array, const int row, const int col) {
    int max_proc = sysconf(_SC_NPROCESSORS_ONLN);
    int *shared_i = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_i == MAP_FAILED)
        return NULL;
    int *new_arr = mmap(NULL, row * col * sizeof(int), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (new_arr == MAP_FAILED) {
        munmap(shared_i, sizeof(int));
        return NULL;
    }

    *shared_i = -1;
    for (int k = 0; k < max_proc && *shared_i < col; ++k) {
        int pid = fork();
        if (!pid) {
            while (++(*shared_i) < col) {
                for (int j = 0; j < row; ++j)
                    new_arr[(*shared_i) * row + j] = array[(row - j) * col - 1 - (*shared_i)];
            }
            exit(0);
        } else if (pid == -1) {
            printf("an error occured\n");
            exit(0);
        }
    }
    int status, n = 0, m;
    int *res = malloc(sizeof(int) * col * row);
    for (int i = 0; i < max_proc;) {
        m = (*shared_i - max_proc) * row;
        if (m > n) {
            memcpy(&res[n], &new_arr[n], m * sizeof(int));
            n = m;
        }
        waitpid(-1, &status, WNOHANG);
        if (status == 0) {
            ++i;
            status = 0;
        }
    }
    memcpy(&res[n], &new_arr[n], (col * row - m) * sizeof(int));
    munmap(shared_i, sizeof(int));
    munmap(new_arr, col * row);
    return res;
}
