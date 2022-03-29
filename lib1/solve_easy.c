#include "easy_method.h"

int **solve(int **arr, int cols, int rows) {
    int **new_arr = (int **) calloc(cols, sizeof(int *));

    for (int i = 0; i < cols; i++)
        new_arr[i] = (int *) malloc(rows * sizeof(int));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            new_arr[cols - 1 - j][rows - 1 - i] = arr[i][j];
    }
    return new_arr;
}