/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/
#include "goldbach_omp_mpi.hpp"
#include <omp.h>

int GoldbachNumbers::primes(int64_t value) {
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

void GoldbachNumbers::goldbach_odd(Number* numberT, size_t thread_count) {
  int64_t number = numberT->number;
  int64_t sums = 0;
  int64_t prime_3 = 0;

  if (number < -5) {  // if the number is smaller than -5, multiplies it by -1
    number = (number *-1);
    numberT->positive = false;
  } else {
    numberT->positive = true;
  }
  // matrix to add the sums temporarily
  std::vector<std::vector<int64_t>> results;
  // matrix takes its size according to the number of threads
  results.resize(thread_count);
  #pragma omp parallel for num_threads(thread_count) default(none) \
      shared(number, sums, results, numberT) schedule(static) private(prime_3)
  // returns the first prime number of the sum
  for (int64_t prime_1 = 2; prime_1 <= number / 2; prime_1++) {
    // continue if the first number is prime
    if (primes(prime_1)) {
      for (int64_t prime_2 = prime_1; prime_2 <= number / 2; prime_2++) {
        // continue if the second number is prime
        if (primes(prime_2)) {
          prime_3 = number - (prime_1 + prime_2);
          // validates that the selected numbers are prime
          if (primes(prime_3) && prime_3 >= prime_2) {
            // if the number is negative,
            // count the amount of sums and save them into an array
            if (!numberT->positive) {
              int my_num = omp_get_thread_num();
              // save the primes numbers part of the sums, into the array
              results[my_num].push_back(prime_1);
              results[my_num].push_back(prime_2);
              results[my_num].push_back(prime_3);
            }
            #pragma omp critical
            // count the sums
            ++sums;
            }
          }
        }
      }
  }
  // add the sums from the local matrix into the vector of sums
  for (size_t i =0 ; i < results.size(); i++) {
    for (size_t j = 0; j < results[i].size() ; j++) {
      numberT->sums.push_back(results[i][j]);
    }
  }
  numberT->sumsAmount = sums;
}

void GoldbachNumbers::goldbach_even(Number* numberT, size_t thread_count) {
  int64_t number = numberT->number;
  int64_t sums = 0;
  int64_t prime_2 = 0;

  if (number < -5) {  // if the number is smaller than -5, multiplies it by -1
    number = number * -1;
    numberT->positive = false;
  } else {
    numberT->positive = true;
  }
  // matrix to add the sums temporarily
  std::vector<std::vector<int64_t>> results;
  // matrix takes its size according to the number of threads
  results.resize(thread_count);
  #pragma omp parallel for num_threads(thread_count) default(none) \
      shared(number, sums, results, numberT) schedule(static) private(prime_2)
  // returns the first prime number of the sum
  for (int64_t prime_1 = 2; prime_1 <= number / 2; prime_1++) {
      // validates that the selected numbers are prime
      if (primes(prime_1)) {
        prime_2 = number - prime_1;
        // if the number is negative,
        // count the amount of sums and save them into an array
        if (primes(prime_2) && prime_2 >= prime_1) {
        if (!numberT->positive) {
          // save the primes numbers part of the sums, into the matrix
          int my_num = omp_get_thread_num();
          results[my_num].push_back(prime_1);
          results[my_num].push_back(prime_2);
        // count the sums
        }
        #pragma omp critical
        ++sums;
      }
    }
  }
  // add the sums from the local matrix into the vector of sums
  for (size_t i =0 ; i < results.size(); i++) {
    for (size_t j = 0; j < results[i].size() ; j++) {
      numberT->sums.push_back(results[i][j]);
    }
  }
  numberT->sumsAmount = sums;
}

void GoldbachNumbers::goldbach(Number* data, size_t thread_count) {
  int64_t number = data->number;
  // if the number is between -5 and 5, is not valid
  if ((number >= -5 && number <= 5)) {
    data->notValid = true;
  } else {
    // for valid numbers
    data->notValid = false;
    // if the number is even
    if (number % 2 == 0) {
      data->even = true;
      goldbach_even(data, thread_count);
      // if the number is odd
    } else {
      data->even = false;
      goldbach_odd(data, thread_count);
    }
  }
}
