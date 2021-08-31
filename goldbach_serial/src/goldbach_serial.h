// "Copyright [2021] <Hellen Fuentes Artavia>"
#ifndef TAREAS_GOLDBACH_SERIAL_SRC_GOLDBACH_SERIAL_H_
#define TAREAS_GOLDBACH_SERIAL_SRC_GOLDBACH_SERIAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
//#include <sys/random.h>

typedef struct {
  int64_t number;
} number_t;

typedef struct {
  char * sums;
  int cant_sums;
  number_t *numbers;
  int64_t originalNum;
} shared_data_t;

typedef struct {
  shared_data_t* shared_data;
} private_data_t;


void doGoldbach(number_t *array, int64_t actualSize);

#endif  // TAREAS_GOLDBACH_SERIAL_SRC_GOLDBACH_SERIAL_H_
