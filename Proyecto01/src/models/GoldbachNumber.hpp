/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#ifndef SRC_MODELS_GOLDBACHNUMBER_HPP_
#define SRC_MODELS_GOLDBACHNUMBER_HPP_
#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

class GoldbachNumber{
  // private variables
 private:
  int64_t number;
  bool positive;
  bool even;
  int64_t amountSums;
  std::string alphanumeric;

  // public variables and methods
 public:
  bool validN;
  std::vector<int64_t> sums;
  /**
  * @brief Class constructor
  * @param alphanumeric: alphanumeric value for each number;
  */ 
  explicit GoldbachNumber(std::string alphanumeric);

  /**
  * @brief Class destroyer
  */ 
  ~GoldbachNumber();

  /**
  * @brief store the absolute value of the number entered by user
  * @param number: absolute value of number entered by user
  */ 
  void setNumber(int64_t number);

  /**
  * @brief set if the original number was positive
  * @param isPositive: if the original number was positive
  */ 
  void setPositive(bool isPositive);

  /**
  * @brief set if the number is even
  * @param isEven: state of the number even = true;
  */ 
  void setEven(bool isEven);

  /**
  * @brief set the amount of Goldbach sums
  * @param amount: amount of Goldbach sums for the number
  */ 
  void setAmountSums(int64_t amount);

  /**
  * @brief get the valid number for Goldbach
  * @return absolute value of the number entered by user
  */ 
  int64_t getNumber();

  /**
  * @brief get number sign
  * @return return if the number is positive
  */ 
  bool getPositive();

  /**
  * @brief return the state of number even / odd
  * @return if the number is even
  */ 
  bool getEven();

  /**
  * @brief Prepare and validate the number 
  * @details get the number for goldbach from alphanumeric variable
  */ 
  void prepareNumber();

  /**
  * @brief Validate if the number is negative or positive
  * @details for Even or Odd numbers
  */ 
  void prepareGoldbach();

  friend std::ostream& operator << (std::ostream& ostream,
                                    const GoldbachNumber& number);
};
#endif  // SRC_MODELS_GOLDBACHNUMBER_HPP_
