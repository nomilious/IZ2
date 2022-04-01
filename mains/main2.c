#include <dlfcn.h>
#include <malloc.h>

#include "header.h"
#include "parallel_matrix.h"

int main(int argc, char **argv) {
    int *arr = NULL;
    int *(*myfunc)(int *, int, int) = NULL;

    void *library = dlopen("build/lib2/libhardlib.so", RTLD_LAZY);  // dlopen("libhardlib.so",...) - fails, Idk why.
    if (!library) {
        printf("ERROR no hardlib\n");
        return 1;
    }

    *(void **) (&myfunc) = dlsym(library, "solve_hard");
    if (!myfunc) {
        dlclose(library);
        printf("ERROR not find func\n");
        return 1;
    }

    if (argc > 1) {
        printf("Dвод из файла\n");
        arr = insert_from_file(argv[1], ROWS, COLS);
    } else {
        printf("Dвод c клавы\n");
        arr = insert_arr(ROWS, COLS);
    }

    if (!arr) {
        dlclose(library);
        printf("ERROR array\n");
        return 1;
    }

    int *result = (*myfunc)(arr, ROWS, COLS);
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
