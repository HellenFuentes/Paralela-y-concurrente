// "Copyright [2021] <Hellen Fuentes Artavia>"
#ifndef SRC_GOLDBACH_PTHREAD_H_
#define SRC_GOLDBACH_PTHREAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
//#include <sys/random.h>
#include <unistd.h>
#include <inttypes.h>

typedef struct {
  bool positive;
  bool even;
  bool notValid;
  int64_t number;
  int64_t sumsAmount;
  int64_t *sums;
  int64_t actualSize;
  int64_t numberAmount;
} number_t;

typedef struct {
  number_t *numbers;
  size_t used;
  size_t size;
} shared_data_t;

typedef struct {
  shared_data_t * sharedData;
  int64_t actualSize;
  int64_t workAssigned;
  int64_t *work;
} private_data_t;

/**
* @brief run the Goldbach Conjecture
* @details creates the threads, and assing work to each. Calls the method that performs the goldbach conjecture
*/
void run_goldbach(size_t num_threads);


#endif  // SRC_GOLDBACH_PTHREAD_H_
