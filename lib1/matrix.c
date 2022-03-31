#include "matrix.h"

int *solve(const int *arr, const int rows, const int cols) {
    int *new_arr = (int *) malloc(rows * cols * sizeof(int));
    if (!new_arr)
        return NULL;

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++)
            new_arr[i * rows + j] = arr[(rows - 1 - j) * cols + (cols - 1 - i)];
    }
    return new_arr;
}
inline int *insert_arr(const int row, const int col, const int max_n) {
    int *arr = (int *) malloc(row * col * sizeof(int));
    if (!arr)
        return NULL;
    srand(time(NULL));

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            arr[i * col + j] = rand() % max_n;
    }
    return arr;
}
void output(const int *arr, const int row, const int col) {
    for (int i = 0; i < row * col; ++i) {
        printf("%d", i);
    }
}
