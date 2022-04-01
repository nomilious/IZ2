#include "header.h"

int *insert_arr(const size_t row, const size_t col) {
    int *arr = (int *) malloc(row * col * sizeof(int));
    if (!arr)
        return NULL;
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++)
            if (!scanf("%d", &arr[i * col + j]))
                return NULL;
    }
    return arr;
}
int *insert_from_file(char *name, const size_t row, const size_t col) {
    int *arr = (int *) malloc(row * col * sizeof(int));
    if (!arr)
        return NULL;
    FILE *f = fopen(name, "r");
    if (!f) {
        free(arr);
        return NULL;
    }
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++)
            if (!fscanf(f, "%d", &arr[i * col + j]))
                return NULL;
    }
    fclose(f);
    return arr;
}
