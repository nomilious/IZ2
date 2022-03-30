#include <malloc.h>

#include "matrix.h"
#define ROWS 10000
#define COLS 5000

void output(int *, int, int);
int *insert_arr(int row, int col, int max_n);
int main() {
    int *arr = NULL;
    int *result = NULL;

    arr = insert_arr(ROWS, COLS, 10);
    if (!arr) {
        printf("EROOR\n");
        return 1;
    }
    result = solve(arr, ROWS, COLS);
    if (!result) {
        free(arr);
        printf("EROOR\n");
        return 1;
    }
    free(arr);
    free(result);

    return 0;
}
void output(int *arr, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            printf("%d ", arr[i * col + j]);
        printf("\n");
    }
}
int *insert_arr(int row, int col, int max_n) {
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