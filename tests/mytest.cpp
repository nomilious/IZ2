#include <gtest/gtest.h>
#include <malloc.h>
extern "C" {
#include "matrix.h"
#include "parallel_matrix.h"
}
inline int *create_arr(const int row, const int col, const int max_n) {
    int *arr = (int *) malloc(row * col * sizeof(int));
    if (!arr)
        return NULL;
    srand(time(NULL));

    for (size_t i = 0; (int) i < row; i++) {
        for (size_t j = 0; (int) j < col; j++)
            arr[i * col + j] = rand() % max_n;
    }
    return arr;
}
inline void gen_res(int *my_res, int *arr, const int row, const int col) {
    for (size_t i = 0; (int) i < col; ++i) {
        for (size_t j = 0; (int) j < row; ++j)
            my_res[i * row + j] = arr[(row - 1 - j) * col + (col - 1 - i)];
    }
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
    if (!my_res) {
        free(arr);
        free(res);
        return;
    }
    gen_res(my_res, arr, row, col);
    for (size_t i = 0; i < row * col; ++i)
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
    if (!my_res) {
        free(arr);
        free(res);
        return;
    }

    gen_res(my_res, arr, row, col);
    for (size_t i = 0; i < row * col; ++i)
        EXPECT_EQ(my_res[i], res[i]);
    free(my_res);
    free(res);
    free(arr);
}
