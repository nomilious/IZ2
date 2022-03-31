#include <dlfcn.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#include "parallel_matrix.h"

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
    int *(*myfunc)(int *, int, int) = NULL;
    int *arr = NULL;

    void *library = dlopen("libhardlib.so", RTLD_LAZY);
    if (!library) {
        printf("ERROR 1\n");
        return 1;
    }

    *(void **) (&myfunc) = dlsym(library, "solve_hard");
    if (!myfunc) {
        dlclose(library);
        printf("ERROR not find func\n");
        return 1;
    }
    arr = insert_arr(ROWS, COLS);

    if (!arr) {
        dlclose(library);
        printf("ERROR array\n");
        return 1;
    }

    int *result = myfunc(arr, ROWS, COLS);
    if (!result) {
        dlclose(library);
        free(arr);
        printf("ERROR in func\n");
        return 1;
    }
    free(arr);
    free(result);
    dlclose(library);

    return 0;
}