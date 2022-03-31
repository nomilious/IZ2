#include <dlfcn.h>
#include <malloc.h>

#include "matrix.h"
#include "parallel_matrix.h"

#define ROWS 10000
#define COLS 5000
int main() {
    int *(*myfunc)(int *, int, int) = NULL;

    void *library = dlopen("libhardlib.so", RTLD_LAZY);
    if (!library) {
        printf("ERROR 1\n");
        return 1;
    }

    *(void **) (&myfunc) = dlsym(library, "solve_hard");
    if (!myfunc) {
        dlclose(library);
        printf("ERROR\n");
        return 1;
    }

    int *arr = insert_arr(ROWS, COLS, 10);
    if (!arr) {
        dlclose(library);
        printf("ERROR\n");
        return 1;
    }

    int *result = myfunc(arr, ROWS, COLS);
    if (!result) {
        dlclose(library);
        free(arr);
        printf("ERROR\n");
        return 1;
    }
    free(arr);
    free(result);
    dlclose(library);

    return 0;
}
