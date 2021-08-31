/*
* Copyright 2021 Jeisson Hidalgo-Cespedes - Universidad de Costa Rica
*/
#ifndef QUEUE_H
#define QUEUE_H
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include "goldbach_optimization.h"

#define EXPAND_SIZE 700

typedef struct queue_node {
  number_t* goldbachNumber;
  struct queue_node* next;
} queue_node_t;

/**
 * Thread-safe queue
 */
typedef struct queue {
  queue_node_t* head;
  queue_node_t* tail;
  pthread_mutex_t can_access_queue;
} queue_t;

int queue_init(queue_t* queue);
int queue_destroy(queue_t* queue);
bool queue_is_empty(queue_t* queue);
int queue_append(queue_t* queue, number_t* data);
/**
 * @remarks Queue must be not empty, otherwise it will crash
 */
number_t* queue_dequeue(queue_t* queue);
int queue_free(queue_t* queue);

#endif  // QUEUE_H