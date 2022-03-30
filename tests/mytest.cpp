#include <gtest/gtest.h>
extern "C" {
#include "../lib1/matrix.h"
#include "../lib2/parallel_matrix.h"
}
TEST(matrix_test, Test_everything) {
    const int row = 10;
    const int col = 5;
    int *arr = insert_arr(row, col, 10);
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
    const int row = 20;
    const int col = 10;
    int *arr = insert_arr(row, col, 10);
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
