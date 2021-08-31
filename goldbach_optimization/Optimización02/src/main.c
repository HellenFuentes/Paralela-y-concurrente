#include "prodcons.h"

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  size_t numberThreads = 0;

  if (argc == 2) {
    if (sscanf(argv[1], "%zu", &numberThreads) != 1 || errno) {
      fprintf(stderr, "error: invalid thread count\n");
      error = 1;
    }
  }

  // run_goldbach(numberThreads);
  if (numberThreads == 0) {
    numberThreads = sysconf(_SC_NPROCESSORS_ONLN);
  }

  // create threads consumer threads
  createThreads(numberThreads);

  return error;
}
