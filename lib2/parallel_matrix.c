#include "parallel_matrix.h"

inline int *solve_hard(const int *array, const int row, const int col) {
  int max_proc = sysconf(_SC_NPROCESSORS_ONLN);
  int *shared_i = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE,
                       MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (shared_i == MAP_FAILED)
    return NULL;
  int *new_arr = mmap(NULL, row * col * sizeof(int), PROT_WRITE,
                      MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  if (new_arr == MAP_FAILED) {
    munmap(shared_i, sizeof(int));
    return NULL;
  }

  *shared_i = -1;
  for (int k = 0; k < max_proc && *shared_i < col; ++k) {
    int pid = fork();
    if (!pid) {
      int nr = ++(*shared_i);
      while (nr < col) {
        for (int j = 0; j < row; ++j)
          new_arr[nr * row + j] = array[(row - j) * col - 1 - nr];
        nr = ++(*shared_i);
      }
      exit(0);
    } else if (pid == -1) {
      printf("an error occured\n");
      exit(0);
    }
  }
  int inputted = 0;
  int *res = malloc(sizeof(int) * col * row);
  while (*shared_i < col) {
    int stat;
    int m = (*shared_i - max_proc) *
            row; // - max_proc, т.к эти строки мож\гут быть в разработке, т.е
                 // над ними еще процесы будут работать
    if (m > inputted) {
      memcpy(&res[inputted], &new_arr[inputted],
             (m - inputted + 1) * sizeof(int));
      inputted = m + 1;
    }
    waitpid(-1, &stat, WNOHANG);
  }
  memcpy(&res[inputted], &new_arr[inputted],
         (row * col - inputted) * sizeof(int));
  munmap(shared_i, sizeof(int));
  munmap(new_arr, col * row);
  return res;
}
