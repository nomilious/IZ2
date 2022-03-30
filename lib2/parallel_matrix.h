#ifndef HEADER_PARALLEL
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define HEADER_PARALLEL

int *solve_hard(const int *, const int, const int);
int *insert_arr(const int, const int, const int);
#endif