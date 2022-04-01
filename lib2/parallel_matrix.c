#include "parallel_matrix.h"

int *solve_hard(const int *array, const int row, const int col) {
    int num_proc = sysconf(_SC_NPROCESSORS_ONLN);
    int *arr_col = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (arr_col == MAP_FAILED)
        return NULL;
    int *res = malloc(sizeof(int) * col * row);
    if (!res) {
        munmap(arr_col, sizeof(int));
        return NULL;
    }
    int *new_arr = mmap(NULL, row * col * sizeof(int), PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (new_arr == MAP_FAILED) {
        free(res);
        munmap(arr_col, sizeof(int));
        return NULL;
    }
    *arr_col = -1;
    for (size_t k = 0; (int) k < num_proc && *arr_col < col; ++k) {
        int pid = fork();
        if (!pid) {
            size_t nr = ++(*arr_col);
            while ((int) nr < col) {
                for (size_t j = 0; (int) j < row; ++j)
                    new_arr[nr * row + j] = array[(row - j) * col - 1 - nr];
                nr = ++(*arr_col);
            }
            exit(0);
        } else if (pid == -1) {
            printf("an error occured\n");
            exit(-1);
        }
    }
    while (*arr_col < col)
        wait(NULL);
    memcpy(res, new_arr, (row * col) * sizeof(int));
    munmap(arr_col, sizeof(int));
    munmap(new_arr, row * col * sizeof(int));
    return res;
}
