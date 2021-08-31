/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/
#ifndef PRODCONS_H
#define PRODCONS_H
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#include <sys/random.h>
#include <unistd.h>
#include "queue.h"

// shared struct
typedef struct {
  queue_t queue;

  size_t units_produced;
  size_t units_consumed;
  number_t* stopCondition;
  number_t* numbersProcessed;

  // semaphore
  sem_t can_consume;
  int size;
} podcons_t;

void *consume(void *data);
void produce(podcons_t *shared_data, size_t numberThreads);
void createThreads(size_t numberThreads);

#endif  // PRODCONS_H