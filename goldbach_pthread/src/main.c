// "Copyright [2021] <Hellen Fuentes Artavia>"
#include "goldbach_pthread.h"


int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  size_t numberThreads = 0;

  if (argc == 2) {
    if (sscanf(argv[1], "%zu", &numberThreads) != 1 || errno) {
      fprintf(stderr, "error: invalid thread count\n");
      error = 1;
    }
  }
  run_goldbach(numberThreads);
  return error;
}
