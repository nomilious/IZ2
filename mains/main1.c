#include <malloc.h>
#define ROWS 10000
#define COLS 5000
#include "matrix.h"

int main() {
  int *arr = NULL;
  int *result = NULL;

  arr = insert_arr(ROWS, COLS, 10);
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
