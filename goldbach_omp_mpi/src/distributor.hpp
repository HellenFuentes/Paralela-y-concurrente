/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/
#ifndef DISTRUBUTOR_HPP
#define DISTRUBUTOR_HPP
#include <vector>
#include "number.hpp"
#include "goldbach_omp_mpi.hpp"

class Distributor {
 public:
  ~Distributor();
  std::vector<int64_t> numbers;
  std::vector<Number*> nums;

  /**
  * @brief adds number to a Number vector
  * @param Number that is going to be in the vector
  */
  void addNum(int64_t number);

  /**
  * @brief calculates the goldbach sums stored in the vector
  * @details this method is used only if there is only one process
  * @param thread_count thread calculators amount
  */
  void calculate(size_t thread_count);

  /**
  * @brief calculates the goldbach sums stored in the vector
  * @details this method is used only if the user uses more than 
  * one process
  * @param thread_count thread calculators amount
  */
  void calculateDistributed(size_t thread_count, int argc, char *argv[]);

   /**
   * @brief prints the results of the Goldbach Conjecture, given an especific number
   * @details the given number are stored in the numberT array
   * @param number to which you want to print the results of the Goldbach conjecture
   */
  void printSums(Number* number);

   /**
   * @brief calls printSums for each number
   */
  void print();

 private:
  GoldbachNumbers *goldbach;
  void sendWork();
  void receiveWork(size_t thread_count);
};

#endif  //DISTRUBUTOR_HPP
