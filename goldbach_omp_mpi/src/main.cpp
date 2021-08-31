/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/
#include <omp.h>
#include "goldbach_omp_mpi.hpp"
#include "number.hpp"
#include "distributor.hpp"

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  size_t numberThreads = 0;
  FILE *input = stdin;
  int64_t number = 0;
  Distributor dist;

  if (argc == 2) {
    if (sscanf(argv[1], "%zu", &numberThreads) != 1 || errno) {
      fprintf(stderr, "error: invalid thread count\n");
      error = 1;
    }
  }

  if (numberThreads == 0) {
    numberThreads = omp_get_max_threads();
  }

  while (fscanf(input, "%ld", &number) == 1) {
    dist.addNum(number);
  }

  dist.calculate(numberThreads);
  dist.print();

  dist.~Distributor();

  return error;
}
