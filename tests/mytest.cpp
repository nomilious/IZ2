#include <gtest/gtest.h>
#include <malloc.h>
extern "C" {
#include "matrix.h"
#include "parallel_matrix.h"
}
inline int *create_arr(const int row, const int col, int max_n) {
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
TEST(matrix_test, Test_everything) {
    const int row = 10;
    const int col = 5;
    int *arr = create_arr(row, col, 10);
    if (!arr)
        return;
    int *res = solve(arr, row, col);
    if (!res) {
        free(arr);
        return;
    }
    int *my_res = (int *) malloc(row * col * sizeof(int));
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j)
            my_res[i * row + j] = arr[(row - 1 - j) * col + (col - 1 - i)];
    }
    for (int i = 0; i < row * col; ++i)
        EXPECT_EQ(my_res[i], res[i]);
    free(my_res);
    free(res);
    free(arr);
}
TEST(parallel_test, Test_everything) {
    const int row = 200000;
    const int col = 1000;
    int *arr = create_arr(row, col, 10);
    if (!arr)
        return;
    int *res = solve_hard(arr, row, col);
    if (!res) {
        free(arr);
        return;
    }
    int *my_res = (int *) malloc(row * col * sizeof(int));
    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j)
            my_res[i * row + j] = arr[(row - 1 - j) * col + (col - 1 - i)];
    }
    for (int i = 0; i < row * col; ++i)
        EXPECT_EQ(my_res[i], res[i]);
    free(my_res);
    free(res);
    free(arr);
}
