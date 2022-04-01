#include "matrix.h"

int *solve(const int *arr, const size_t rows, const size_t cols) {
    int *new_arr = (int *) malloc(rows * cols * sizeof(int));
    if (!new_arr)
        return NULL;
    // матрица a[ROWS][COLS] превращается в a[COLS][ROWS]
    for (size_t i = 0; i < cols; i++) {
        for (size_t j = 0; j < rows; j++)
            new_arr[i * rows + j] = arr[(rows - 1 - j) * cols + (cols - 1 - i)];
    }
    return new_arr;
}
