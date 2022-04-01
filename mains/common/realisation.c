#include "header.h"

int *insert_arr(const int row, const int col) {
    int *arr = (int *) malloc(row * col * sizeof(int));
    if (!arr)
        return NULL;
    for (size_t i = 0; (int) i < row; i++) {
        for (size_t j = 0; (int) j < col; j++)
            if (!scanf("%d", &arr[i * col + j]))
                return NULL;
    }
    return arr;
}
int *insert_from_file(char *name, const int row, const int col) {
    int *arr = (int *) malloc(row * col * sizeof(int));
    if (!arr)
        return NULL;
    FILE *f = fopen(name, "r");
    for (size_t i = 0; (int) i < row; i++) {
        for (size_t j = 0; (int) j < col; j++)
            if (!fscanf(f, "%d", &arr[i * col + j]))
                return NULL;
    }
    fclose(f);
    return arr;
}
