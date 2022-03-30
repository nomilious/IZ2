#include <dlfcn.h>
#include <malloc.h>

#include "parallel_matrix.h"
#define ROWS 10000
#define COLS 5000

void output(int *, int, int);
int *insert_arr(int row, int col, int max_n);
int main() {
    int *arr = NULL;
    int *result = NULL;
    int *(*myfunc)(int *, int, int) = NULL;
    void *library = NULL;

    library = dlopen("libhardlib.so", RTLD_LAZY);
    if (!library) {
        printf("ERROR 1\n");
        return 1;
    }

    *(void **) (&myfunc) = dlsym(library, "solve_hard");
    if (!myfunc) {
        printf("ERROR\n");
        return 1;
    }
    arr = insert_arr(ROWS, COLS, 10);

    if (!arr) {
        printf("ERROR\n");
        return 1;
    }
    result = myfunc(arr, ROWS, COLS);
    if (!result) {
        free(arr);
        printf("ERROR\n");
        return 1;
    }
    free(arr);
    munmap(result, COLS * ROWS);
    dlclose(library);

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