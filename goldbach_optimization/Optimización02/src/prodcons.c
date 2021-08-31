/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/
#include "prodcons.h"

/**
* @brief implemets a producer that insert to the queue
* @param shared_data as the data that share the consumers
* @param numberThreads as the number of threads created
*/
void produce(podcons_t *shared_data, size_t numberThreads) {
  // initialice variables
  int64_t number = 0ll;
  FILE* input = stdin;
  int tamanio = 0;
  int contador = 0;

  // allocates memory for shared_data->numbersProcessed
  shared_data->numbersProcessed = (number_t*) calloc(1, sizeof(number_t));

  // gets the numbers given by the user and insert them to the queue
  while (fscanf(input, "%ld", &number) == 1) {
    ++tamanio;
    // resize the array if more space is need it
    shared_data->numbersProcessed = (number_t*)
    realloc(shared_data->numbersProcessed, sizeof(number_t)*(tamanio+1));
    number_t *numberStruct = (number_t*) calloc(1, sizeof(number_t));

    // initialice variables
    numberStruct->number = number;
    numberStruct->actualSize = EXPAND_SIZE;
    numberStruct->even = false;
    numberStruct->notValid = false;
    numberStruct->positive = false;
    numberStruct->sumsAmount = 0;
    numberStruct->numberAmount = 0;

    // insert to queue
    queue_append(&shared_data->queue, numberStruct);
    // increment semaphore
    sem_post(&shared_data->can_consume);
    numberStruct->position = contador;
    ++contador;
  }

  // save sise of struct to shared_data->size
  shared_data->size = tamanio;

  for (size_t i = 0; i < numberThreads; i++) {
    number_t *stop = NULL;
    queue_append(&shared_data->queue, stop);
    sem_post(&shared_data->can_consume);
  }
}

/**
* @brief implemets a producer that insert to the queue
* @param data as the data that receive the consumers
* @return NULL after consuming the queue
*/
void *consume(void *data) {
  // calls the prodcons struct
  podcons_t *prodcons = (podcons_t *) data;

  while (true) {
    // makes the semaphore to wait
    sem_wait(&prodcons->can_consume);

    // get out from the queue
    number_t* value = queue_dequeue(&prodcons->queue);
    if (value == prodcons->stopCondition) {
      break;
    } else {
      // calls the goldbach conjecture
      goldbach(value);
      prodcons->numbersProcessed[value->position] = *value;
    }
  }
  return NULL;
}

/**
* @brief create and join threads for consumers
* @param numberThreads as the number of threads created fot consumers
*/
void createThreads(size_t numberThreads) {
  // Allocate memory for shared data between threads
  podcons_t *shared_data = (podcons_t *)calloc(1, sizeof(podcons_t));
  shared_data->stopCondition = NULL;

  // queue and semaphore init
  queue_init(&shared_data->queue);
  sem_init(&shared_data->can_consume, 0, 0);

  // Allocate memory for consumer threads
  pthread_t *consumers = (pthread_t *)calloc(numberThreads, sizeof(pthread_t));
  for (size_t i = 0; i < numberThreads; ++i) {
    // Create threads for consume
    pthread_create(&consumers[i], NULL, consume, (void *)shared_data);
  }

  // calls the producer method
  produce(shared_data, numberThreads);

  for (size_t i = 0; i < numberThreads; ++i) {
    // join the consumer threads
    pthread_join(consumers[i], NULL);
  }

  // print all the numbers and their sums
  for (int amountNum = 0 ; amountNum < shared_data->size; amountNum++) {
      printN(shared_data->numbersProcessed[amountNum]);
    }

  // frees allocated memory
  sem_destroy(&shared_data->can_consume);
  queue_free(&shared_data->queue);

  free(shared_data);
}
