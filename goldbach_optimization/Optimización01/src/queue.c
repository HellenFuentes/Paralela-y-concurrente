/*
* Copyright 2021 Jeisson Hidalgo-Cespedes - Universidad de Costa Rica
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "queue.h"

bool queue_is_empty_private(const queue_t* queue);

int queue_init(queue_t* queue) {
  assert(queue);
  return pthread_mutex_init(&queue->can_access_queue, /*attr*/NULL);
}

int queue_destroy(queue_t* queue) {
  assert(queue);
  return pthread_mutex_destroy(&queue->can_access_queue);
}

bool queue_is_empty_private(const queue_t* queue) {
  assert(queue);
  return queue->head == NULL;
}

int queue_append(queue_t* queue, number_t* data) {
  assert(queue);
  int error = 0;

  queue_node_t* new_node = (queue_node_t*)calloc(1, sizeof(queue_node_t));
  if (new_node) {
    new_node->goldbachNumber = data;

    pthread_mutex_lock(&queue->can_access_queue);
    if (queue_is_empty_private(queue)) {
      queue->head = queue->tail = new_node;
    } else {
      queue->tail = queue->tail->next = new_node;
    }
    pthread_mutex_unlock(&queue->can_access_queue);
  } else {
    fprintf(stderr, "error: could not allocate memory for a queue node\n");
    error = 41;
  }

  return error;
}

bool queue_is_empty(queue_t* queue) {
  assert(queue);

  pthread_mutex_lock(&queue->can_access_queue);
  bool result = queue->head == NULL;
  pthread_mutex_unlock(&queue->can_access_queue);

  return result;
}

int queue_free(queue_t* queue) {
  assert(queue);
  while (!queue_is_empty_private(queue)) {
    queue_dequeue(queue);
  }
  pthread_mutex_destroy(&queue->can_access_queue);
  return 0;
}

number_t* queue_dequeue(queue_t* queue) {
  assert(queue);

  pthread_mutex_lock(&queue->can_access_queue);
  assert(queue_is_empty_private(queue) == false);

  queue_node_t* first = queue->head;
  number_t* data = first->goldbachNumber;
  queue->head = first->next;
  free(first);
  if (queue->head == NULL) {
    queue->tail = NULL;
  }
  pthread_mutex_unlock(&queue->can_access_queue);

  return data;
}
