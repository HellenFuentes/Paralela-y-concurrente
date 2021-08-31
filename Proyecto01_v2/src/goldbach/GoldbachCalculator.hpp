/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#ifndef SRC_MODELS_GOLDBACHCALCULATOR_HPP_
#define SRC_MODELS_GOLDBACHCALCULATOR_HPP_
#include <string>
#include "GoldbachNumber.hpp"

class GoldbachCalculator {
 private:

 public:
  /**
  * @brief Class constructor
  */  
  GoldbachCalculator();
  /**
  * @brief Class destroyer
  */ 
  ~GoldbachCalculator();

  /**
  * @brief Look for the sums to Strong Conjecture
  * @details this method looking for strong conjecture sums and print if required
  * @param number:number for Goldbach strong conjecture
  * @return 
  */
  void strongConjecture(GoldbachNumber* number);

  /**
  * @brief Look for the sums to Weak Conjecture
  * @details this method looking for Weak conjecture sums and print if required
  * @param number:number for Goldbach weak conjecture
  * @return 
  */
  void weakConjecture(GoldbachNumber* number);
  /**
  * @brief check that the number is prime
  * @details adaptado de: https://bit.ly/35iaFhy
  * @param number: number to verify
  * @return if the number is prime then return PRIME("1") otherwise return NO_PRIME
  *
  */
  int64_t primes(int64_t number);
  /**
  * @brief Start goldbach
  * @param data: data for goldbach
  * @return NULL
  *
  */
  void* startGoldbach(void* data);
};

#endif  // SRC_MODELS_GOLDBACHCALCULATOR_HPP_
