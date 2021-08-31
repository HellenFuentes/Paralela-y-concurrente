// "Copyright [2021] <Hellen Fuentes Artavia>"
#include <stdio.h>
#include <stdlib.h>
#include "goldbach_serial.h"

int main(void) {
  int64_t number = 0ll;
  FILE* input = stdin;
  int index = 0;
  int tamanio = 0;
  shared_data_t* array = calloc(tamanio, sizeof(shared_data_t));
  array->numbers = (number_t*) calloc(1, sizeof(number_t));

  while (fscanf(input, "%ld", &number) == 1) {
    ++tamanio;
    number_t* expandido = (number_t*) realloc (array->numbers, tamanio *sizeof(number_t));
    array->numbers = expandido;
    array->numbers[index].number = number;
    ++index;
  }
  doGoldbach(array->numbers,tamanio);
}
