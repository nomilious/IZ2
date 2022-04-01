#include <malloc.h>

#include "header.h"
#include "matrix.h"

int main(int argc, char **argv) {
    int *arr = NULL;
    int *result = NULL;
    if (argc > 1) {
        printf("Ввод из файла\n");
        arr = insert_from_file(argv[1], ROWS, COLS);
    } else {
        printf("Ввод c клавы\n");
        arr = insert_arr(ROWS, COLS);
    }
    if (!arr) {
        printf("ERROR arr\n");
        return 1;
    }
    result = solve(arr, ROWS, COLS);
    if (!result) {
        free(arr);
        printf("ERROR to solve()\n");
        return 1;
    }
    free(arr);
    free(result);

    return 0;
}
