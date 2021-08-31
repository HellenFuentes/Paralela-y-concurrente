// "Copyright [2021] <Hellen Fuentes Artavia>"
#include "goldbach_pthread.h"
#define EXPAND_SIZE 500

/**
* @brief increment the size of an array
* @details sums the defined EXPAND_SIZE to the previous size
* @param array to which you want to expand its size, and the previous oldSize
* @param oldSize as the previous Size
 */
int64_t* incrementArray(int64_t *array, int oldSize) {
  int64_t *ret = NULL;
  // EXPAND_SIZE because when doing reallocs for
  // each sum requires a lot of processing power
  int newSize = oldSize + EXPAND_SIZE;
  int64_t *new = realloc(array, sizeof(int64_t)*newSize);
  if (new) {
    ret = new;
  }
  return ret;
}

/**
* @brief Validates if the entered value is a prime
* @param value to be validated
* @return Isprime = true, when the entered number is prime
*/
int primes(int64_t value) {
    bool isPrime = true;

  // 0 and 1 are not prime numbers
  if (value == 0 || value == 1) {
    isPrime = false;
  } else {
    for (int64_t numbers  = 2; numbers <= value / 2; ++numbers) {
      if (value % numbers == 0) {
        isPrime = false;
        break;
      }
    }
  }
  return isPrime;
}

/**
* @brief calculates sums of primes for odd number values
* @details if the number is odd three prime numbers are added as part of its sum
* @param numberT as the array that contents the numbers to which you want to apply the Goldbach conjecture
 */
void goldbach_odd(number_t* numberT) {
  int64_t number = numberT->number;
  int64_t sums = 0;
  int64_t index = 0;
  int64_t tamanio = 0;
  int64_t tamanio_actual = EXPAND_SIZE;

  if (number < -5) {  // if the number is smaller than -5, multiplies it by -1
    number = (number *-1);
    numberT->positive = false;
  } else {
    numberT->positive = true;
  }
  // returns the first prime number of the sum
  for (int64_t prime_1 = 2; prime_1 < number - 2; prime_1++) {
    // returns the second prime number of the sum
    for (int64_t prime_2 = prime_1; prime_2 < number - 2; prime_2++) {
      // returns the third prime number of the sum
      for (int64_t prime_3 = prime_2; prime_3 < number - 2; prime_3++) {
        // validates that the selected numbers are prime
        if ((prime_1 + prime_2 + prime_3 == number) && primes(prime_1)
          && primes(prime_2) && primes(prime_3)) {
          // if the number is negative,
          // count the amount of sums and save them into an array
          if (!numberT->positive) {
            if ((tamanio + 3) >=tamanio_actual) {
              // increments the array depending of the
              // amount of numbers that needs to be added to it
              numberT->sums = incrementArray(numberT->sums, tamanio_actual);
              tamanio_actual = tamanio_actual + EXPAND_SIZE;
              numberT->actualSize = tamanio_actual;
            }
            // save the primes numbers part of the sums, into the array
            numberT->sums[index++] = prime_1;
            ++tamanio;
            numberT->sums[index++] = prime_2;
            ++tamanio;
            numberT->sums[index++] = prime_3;
            ++tamanio;
            // increments the amount of sums
            ++sums;
            numberT->numberAmount = tamanio;
          // else count the sums
          } else {
            ++sums;
          }
        }
      }
    }
  }
  // save the amount of sums into the sumsAmount
  numberT->sumsAmount = sums;
}

/**
* @brief calculates sums of primes for even number values
* @details if the number is even two prime numbers are added as part of its sum
* @param numberT as the array that contents the numbers to which you want to apply the Goldbach conjecture
 */
void goldbach_even(number_t* numberT) {
  int64_t number = numberT->number;
  int64_t sums = 0;
  int64_t index = 0;
  int64_t tamanio = 0;
  int64_t tamanio_actual = EXPAND_SIZE;
  if (number < -5) {  // if the number is smaller than -5, multiplies it by -1
    number = number * -1;
    numberT->positive = false;
  } else {
    numberT->positive = true;
  }
  // returns the first prime number of the sum
  for (int64_t prime_1 = 2; prime_1 < number - 2; prime_1++) {
    // returns the second prime number of the sum
    for (int64_t prime_2 = prime_1; prime_2 < number - 2; prime_2++) {
      // validates that the selected numbers are prime
      if ((prime_1 + prime_2 == number) &&
      primes(prime_1) && primes(prime_2)) {
        // if the number is negative,
        // count the amount of sums and save them into an array
        if (numberT->number <-5) {
          if ((tamanio+2) >= tamanio_actual) {
            // increments the array depending of the
            // amount of numbers that needs to be added to it
            numberT->sums = incrementArray(numberT->sums, tamanio_actual);
            tamanio_actual = tamanio_actual + EXPAND_SIZE;
            numberT->actualSize = tamanio_actual;
          }
          // save the primes numbers part of the sums, into the array
          numberT->sums[index++] = prime_1;
          ++tamanio;
          numberT->sums[index++] = prime_2;
          ++tamanio;
          numberT->numberAmount = tamanio;
          // increments the amount of sums
          ++sums;
        // else count the sums
        } else {
          ++sums;
        }
      }
    }
  }
  // save the amount of sums into the sumsAmount
  numberT->sumsAmount = sums;
}


/**
* @brief prints the results of the Goldbach Conjecture, given an especific number
* @details the given number are stored in the numberT array
* @param number to which you want to print the results of the Goldbach conjecture
*/
void printN(number_t number) {
  // prints the original number
  printf("%ld", number.number);
  printf(": ");
  // if the number is valid (-5 > number > 5)
  if (!number.notValid) {
    // prints the amount of sums
    printf("%ld sums:", number.sumsAmount);
    // if the number is negative
    if (!number.positive) {
      // from the initial number until the last one added to the array
      for (int index = 0; index < number.numberAmount; index++) {
        // if the number is even
        if (number.even) {
          // print the prime numbers part its sum
          printf(" %ld + %ld", number.sums[index], number.sums[index+1]);
          index = index + 1;
          if ((index+1)!= number.numberAmount) {
            printf(",");
          }
          // if the number is odd
        } else {
          // print the prime numbers part its sum
          printf(" %ld + %ld + %ld", number.sums[index],
          number.sums[index+1], number.sums[index+2]);
          index = index + 2;
          if ((index+1)!= number.numberAmount) {
            printf(",");
          }
        }
      }
    }
    // if the number is not valid (-5 < number < 5)
  } else {
    printf("NA");
  }
  printf("\n");
}

/**
* @brief calculates the Goldbach Conjecture that can be done for positive and negative numbers that are out of 5 and -5
* @details calls the goldbach_even method if the number is even, or goldbach_odd if the number is odd
* @param data to which you want to apply the Goldbach conjecture
*/
void* goldbach(void* data) {
  // calls the array where ther numbers are saved
  private_data_t *priv = (private_data_t*) data;
  shared_data_t *sha = priv->sharedData;
  // for the work assing to each thread
  for (int nums = 0 ; nums < priv->workAssigned ; nums++) {
    int64_t indexWork = priv->work[nums];
    number_t* my_number = &sha->numbers[indexWork];
    int64_t number = my_number->number;
    // if the number is between -5 and 5, is not valid
    if ((number >= -5 && number <= 5)) {
      my_number->notValid = true;
    } else {
      // for valid numbers
      my_number->notValid = false;
      // if the number is even
      if (number % 2 == 0) {
        my_number->even = true;
        goldbach_even(my_number);
        // if the number is odd
      } else {
        my_number->even = false;
        goldbach_odd(my_number);
      }
    }
  }
  return NULL;
}

void create_threads(int index, shared_data_t* array, size_t number_threads ) {
  // initialize the variable that defines the amount of threads
  int numberThreads = number_threads;
  if (numberThreads == 0) {
    numberThreads = sysconf(_SC_NPROCESSORS_ONLN);
  }

  // stores memory for the creation of threads and
  // also for the private structure of each one
  pthread_t *threads = (pthread_t *)calloc(numberThreads, sizeof(pthread_t));
  private_data_t *private_data = (private_data_t *)
  calloc(numberThreads, sizeof(private_data_t));

  // initialize the array thar save the num of sums
  for (int num = 0 ; num < index; num++) {
    // allocate space for the sums of each number
    // EXPAND_SIZE why do reallocs for
    // each sum requires a lot of processing power
    array->numbers[num].sums = calloc(EXPAND_SIZE, sizeof(int64_t));
  }

  for (int num = 0; num < numberThreads; ++num) {
      // vector of work for each thread (indexes of work)
      private_data[num].work = calloc(EXPAND_SIZE, sizeof(int64_t));
      // expand the actual size
      private_data[num].actualSize = EXPAND_SIZE;
      // initialize the assigned work for each thread in 0
      private_data[num].workAssigned = 0;
  }

    int workAsign = 0;  // total assigned jobs

    // 1 to 1 mapping by indices
    // index = cant nums
    for (int numPos = 0; numPos < index ; numPos++) {
      for (int amountNum = 0 ; amountNum < numberThreads; amountNum++) {
        // if the amount of work is diferent as the max index
        if (workAsign!= index) {
           // Apunta al vector de trabajos de cada private data
          int64_t* work = private_data[numPos].work;
          // if the assigned work equals the actual size - 1
          if (private_data[numPos].workAssigned ==
          (private_data[numPos].actualSize-1)) {
            // increments the actual size
            work = incrementArray(work, private_data[numPos].actualSize);
            // expand size
            private_data[numPos].actualSize =
            private_data[numPos].actualSize + EXPAND_SIZE;
          }
          // in the current private structure in the minor available position
          // of the vector assign the current job.
          work[private_data[numPos].workAssigned] = workAsign;
          ++private_data[numPos].workAssigned;
          ++workAsign;
        }
      }
    }

    for (int index = 0; index < numberThreads; ++index) {
      // the private data pointer now points to the shared structure
      private_data[index].sharedData = array;
      // create threads and calls the method that
      // performs the Goldbach Conjecture
      // threads[index] vector de hilos
      if (pthread_create(&threads[index], /*attr*/ NULL,
      goldbach, &private_data[index]) == EXIT_SUCCESS) {
      } else {
        // if the threads could'nt be created = error
        fprintf(stderr, "error: could not create thread %d\n", index);
        EXIT_FAILURE;
        break;
      }
    }

    // pthread join till the number of threads
    for (int index = 0; index < numberThreads; ++index) {
      pthread_join(threads[index], /*value_ptr*/ NULL);
    }
    // prints the original number and its results from the Goldbach Conjecture
    for (int amountNum = 0 ; amountNum < index ; amountNum++) {
      printN(array->numbers[amountNum]);
    }
    // free the memory allocated for the threads
    free(threads);

    // free the memory allocated for the sums saved
    // into the structure shared_data_t->numbers
    for (int amountNum = 0; amountNum < index ; amountNum++) {
      free(array->numbers[amountNum].sums);
    }

    // free the memory allocated for the work saved
    // into the structure private_data_t
    for (int assignNum = 0; assignNum < numberThreads ; assignNum++) {
      free(private_data[assignNum].work);
    }

    // free the memory allocated for the data saved into
    free(private_data);
    free(array->numbers);
    free(array);
}

void run_goldbach(size_t number_threads) {
  int64_t number = 0ll;
  FILE* input = stdin;
  int index = 0;
  int tamanio = 1;

  // initialize the array that will store the numbers
  shared_data_t* array = calloc(1, sizeof(shared_data_t));
  array->numbers = (number_t*)calloc(1, sizeof(number_t));

  // saves the numbers entered by the user in an array
  while (fscanf(input, "%ld", &number) == 1) {
    ++tamanio;
    // resize the array if more space is need it
    number_t* expandido = (number_t*)
    realloc(array->numbers, tamanio *sizeof(number_t));
    array->numbers = expandido;
    array->numbers[index].number = number;
    array->numbers[index].actualSize = EXPAND_SIZE;
    array->numbers[index].even = false;
    array->numbers[index].notValid = false;
    array->numbers[index].positive = false;
    array->numbers[index].sumsAmount = 0;
    array->numbers[index].numberAmount = 0;
    ++index;
  }
  create_threads(index, array, number_threads);
}
