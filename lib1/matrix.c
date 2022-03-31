#include "matrix.h"

int *solve(const int *arr, const int rows, const int cols) {
  int *new_arr = (int *)malloc(rows * cols * sizeof(int));
  if (!new_arr)
    return NULL;

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++)
      new_arr[i * rows + j] = arr[(rows - 1 - j) * cols + (cols - 1 - i)];
  }
  return new_arr;
}
