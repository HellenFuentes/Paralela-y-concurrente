/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/
#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <vector>
#include "number.hpp"

class GoldbachNumbers{
 public:
  GoldbachNumbers() {}
  ~GoldbachNumbers() {}

  /**
  * @brief calculates the Goldbach Conjecture that can be done for positive and negative numbers that are out of 5 and -5
  * @details calls the goldbach_even method if the number is even, or goldbach_odd if the number is odd
  * @param data to which you want to apply the Goldbach conjecture
  * @param thread_count as the number of threads to work with numbers
  */
  void goldbach(Number* data, size_t thread_count);

 private:
  /**
  * @brief Validates if the entered value is a prime
  * @param value to be validated
  * @return Isprime = true, when the entered number is prime
  */
  int primes(int64_t value);

  /**
  * @brief calculates sums of primes for odd number values
  * @details if the number is odd three prime numbers are added as part of its sum
  * @param numberT as the array that contents the numbers to which you want to apply the Goldbach conjecture
  * @param thread_count as the number of threads to work with numbers
  */
  void goldbach_odd(Number* numberT, size_t thread_count);

  /**
  * @brief calculates sums of primes for even number values
  * @details if the number is even two prime numbers are added as part of its sum
  * @param numberT as the array that contents the numbers to which you want to apply the Goldbach conjecture
  * @param thread_count as the number of threads to work with numbers
  */
  void goldbach_even(Number* numberT, size_t thread_count);
};
