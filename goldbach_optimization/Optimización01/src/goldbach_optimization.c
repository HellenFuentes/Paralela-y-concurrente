/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/
#include "goldbach_optimization.h"
#define EXPAND_SIZE 700

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
    for (int64_t numbers  = 2; numbers*numbers <= value; ++numbers) {
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
void goldbach(number_t* data) {
  data->sums = calloc(EXPAND_SIZE, sizeof(int64_t));
  data->actualSize = EXPAND_SIZE;
  number_t* my_number = data;
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
