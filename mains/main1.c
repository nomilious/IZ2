#include <malloc.h>

#include "matrix.h"
#define ROWS 10000
#define COLS 5000
int *insert_arr(const int row, const int col) {
    int *arr = (int *) malloc(row * col * sizeof(int));
    if (!arr)
        return NULL;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            if (!scanf("%d", &arr[i * col + j]))
                return NULL;
    }
    return arr;
}

int main() {
    int *arr = NULL;
    int *result = NULL;

    arr = insert_arr(ROWS, COLS);
    if (!arr) {
        printf("ERROR\n");
        return 1;
    }
    result = solve(arr, ROWS, COLS);
    if (!result) {
        free(arr);
        printf("ERROR\n");
        return 1;
    }
    free(arr);
    free(result);

    return 0;
}
