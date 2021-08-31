/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/

#ifndef NUMBER_HPP
#define NUMBER_HPP
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <vector>

class Number{
 private:

 public:
  bool positive;
  bool even;
  bool notValid;
  int64_t number;
  int64_t sumsAmount;
  int64_t actualSize;
  int64_t position;

  std::vector <int64_t> sums;

  /**
   * @brief class constructor, initialize variables
   */
  Number() {
  positive = false;
  even = false;
  notValid = false;
  number = 0;
  sumsAmount = 0;
  actualSize = 0;
  position = position;
  }
  ~Number(){}
};

#endif  // NUMBER_HPP
