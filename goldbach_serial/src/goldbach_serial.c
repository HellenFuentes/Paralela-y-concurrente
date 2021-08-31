// "Copyright [2021] <Hellen Fuentes Artavia>"
#include "goldbach_serial.h"

/**
* @brief Validates if the entered value is a prime
* @details Scanf returns value 0 when the value entered is not of the requested format, so if it is not int, it will give an error
* @param value to be validated
* @return 0 if it is not prime, 1 if it is
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
* @brief calculates sums of primes for odd integer values
* @details if the number is odd three prime numbers are added, also if the number is between -5 and 5 it is taken as a case of N / A
* @param number to which you want to apply the Goldbach conjecture
 */
void goldbach_odd(int64_t number) {
  shared_data_t* shared_data = (shared_data_t*)
  calloc(1, sizeof(shared_data_t));

  int size = 100;
  shared_data->cant_sums = 0;
  shared_data->originalNum = number;
  shared_data->sums = (char*)calloc(size, sizeof(char));

  if (number < -5) {  // if the number is smaller than -5, multiplies it by -1
    number = number * -1;
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
            // if the number is smaller than -5, count and shows the sums
            if (shared_data->originalNum < -5) {
              // converts the primes numbers into a string and save it on a vector
             snprintf(&shared_data->sums[strlen(shared_data->sums)],1000, "%ld + %ld + %ld , ",
             (int64_t)prime_1, (int64_t)prime_2, (int64_t)prime_3);
              if (strlen(shared_data->sums) > (size_t)(size / 2)) {
                size += 500;
                // resize the size of the vector
                shared_data->sums = (char*)realloc(shared_data->sums, sizeof(char)*size);
              }
              shared_data->cant_sums++;
            // else count the sums
            } else {
              shared_data->cant_sums++;
            }
        }
      }
    }
  }
  printf("\n%ld : (%d sums) :%s ", shared_data->originalNum, shared_data->cant_sums, shared_data->sums);
  free(shared_data->sums);
  free(shared_data);
}

/**
* @brief calculates sums of primes for even integer values
* @details if the number is eclearven two prime numbers are added, also if the number is between -5 and 5 it is taken as a case of N / A
* @param number to which you want to apply the Goldbach conjecture
*/
void goldbach_even(int64_t number) {
  shared_data_t* shared_data = (shared_data_t*)
  calloc(1, sizeof(shared_data_t));

  shared_data->cant_sums = 0;
  int size = 100;
  shared_data->originalNum = number;
  shared_data->sums = (char*)calloc(size,sizeof(char));

  if (number < -5) {  // if the number is smaller than -5, multiplies it by -1
    number = number * -1;
  }
  // returns the first prime number of the sum
  for (int64_t prime_1 = 2; prime_1 < number - 2; prime_1++) {
    // returns the second prime number of the sum
    for (int64_t prime_2 = prime_1; prime_2 < number - 2; prime_2++) {
      // validates that the selected numbers are prime
        if ((prime_1 + prime_2 == number) &&
          primes(prime_1) && primes(prime_2)) {
            // if the number is smaller than -5, count and shows the sums
            if (shared_data->originalNum <-5) {
              // converts the primes numbers into a string and save it on a vector
              snprintf(&shared_data->sums[strlen(shared_data->sums)], 1000, "%ld + %ld, ",
              (int64_t)prime_1, (int64_t)prime_2);
              if (strlen(shared_data->sums) > (size_t)(size / 2)) {
                size += 500;
                // resize the size of the vector
                shared_data->sums = (char*)realloc (shared_data->sums, sizeof(char)*size);
              }
              shared_data->cant_sums++;
            // else count the sums
            } else {
              shared_data->cant_sums++;
      }
    }
  }
}
  printf("\n%ld : (%d sums) :%s", shared_data->originalNum, shared_data->cant_sums, shared_data->sums);
  free(shared_data->sums);
  free(shared_data);
}

/**
* @brief calculates the sums that can be done for positive and negative integer values that are within -5 to 5
* @details calls the goldbach_even method if the number is even, or goldbach_odd if the number is odd
* @param number to which you want to apply the Goldbach conjecture
*/
void goldbach(int64_t num) {
  if ((num >= -5 && num <= 5)) {
    printf("\n%ld: N/A ", num);
  } else {
     if (num % 2 == 0) {  // if the number is even
      goldbach_even(num);
  } else {  // if the number is odd
      goldbach_odd(num);
        }
    }
}

/**
* @brief calculates the conjeture for all number added to the program
* @details calls the goldbach method
* @param array where the numbers are saved, and the actual size of the array
*/
void doGoldbach(number_t *array, int64_t actualSize) {
  for (int i = 0; i < actualSize; i++) {
    goldbach(array[i].number);
  }
}

