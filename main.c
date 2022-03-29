#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "easy_method.h"
#define ROWS 10000
#define COLS 5000

void output(int **, int, int);
void free2D(int ***arr, int row, int col);
int main() {
    int **result;
    int **arr = (int **) calloc(ROWS, sizeof(int *));

    srand(time(NULL));
    // insert
    for (int i = 0; i < ROWS; i++) {
        arr[i] = (int *) calloc(COLS, sizeof(int));
        for (int j = 0; j < COLS; j++)
            arr[i][j] = rand() % 10;
    }
    // output unresolved
    output(arr, ROWS, COLS);
    printf("\n\n");
    // get resolved
    result = solve(arr, COLS, ROWS);
    // output resolved
    output(result, COLS, ROWS);
    free2D(&result, COLS, ROWS);
    free2D(&arr, ROWS, COLS);

    return 0;
}
void output(int **arr, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}
void free2D(int ***arr, int row, int col) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            free(*arr[i]);
    free(*arr);
}