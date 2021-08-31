/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/
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

typedef struct {
  bool positive;
  bool even;
  bool notValid;
  int64_t number;
  int64_t sumsAmount;
  int64_t *sums;
  int64_t actualSize;
  int64_t numberAmount;
  int64_t position;
} number_t;


void goldbach(number_t* data);
void goldbach_odd(number_t* numberT);
void goldbach_even(number_t* numberT);
void printN(number_t number);


#endif  // SRC_GOLDBACH_PTHREAD_H_
