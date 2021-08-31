/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#include "GoldbachNumber.hpp"
#include <stdio.h>
#include <stdexcept>

GoldbachNumber::GoldbachNumber(std::string alphanumeric) {
  this->number = 0ll;
  this->alphanumeric = alphanumeric;
  this->positive = true;
  this->even = true;
  this->amountSums = 0;
  this->validN = true;
  prepareNumber();
}

void GoldbachNumber::prepareNumber() {
  if (this->alphanumeric.length() > 0) {
    try {
      this->number = stoll(this->alphanumeric, nullptr, 10);
      prepareGoldbach();
    }
    catch(const std::invalid_argument& e) {
      this->validN = false;
    }
    catch(const std::out_of_range& e) {
      this->validN = false;
    }
  }
}

void GoldbachNumber::prepareGoldbach() {
  if (this->number < 0) {
    this->number *= -1;
    this->positive = false;
  }
  if (this->number%2 != 0) {
    this->even = false;
  }
  if (this->number <=5) {
    this->validN = false;
  }
}

GoldbachNumber::~GoldbachNumber() {
}

void GoldbachNumber::setNumber(int64_t number) {
  this->number = number;
}

void GoldbachNumber::setPositive(bool isPositive) {
  this->positive = isPositive;
}

void GoldbachNumber::setEven(bool isEven) {
  this->even = isEven;
}

int64_t GoldbachNumber::getNumber() {
  return this->number;
}

bool GoldbachNumber::getPositive() {
  return this->positive;
}

bool GoldbachNumber::getEven() {
  return this->even;
}

void GoldbachNumber::setAmountSums(int64_t amount) {
  this->amountSums = amount;
}

std::ostream& operator << (std::ostream& ostream,
const GoldbachNumber& goldbachNumber) {
  ostream << "  <style>p{color: black;font-size: large}</style>\n";
  ostream << "<p>";
  if (!goldbachNumber.positive) {
    // turn to the original number
    ostream << "-";
  }
  // print the original number
  ostream << goldbachNumber.number;
  // amount of sums
  ostream << ": ";
  if (goldbachNumber.validN) {
    ostream<< "sums " <<goldbachNumber.amountSums;
    if (!goldbachNumber.positive) {
      // if the original number was negative we have to
      // print the numbers that compose the sums
      ostream << ": ";
      if (goldbachNumber.even) {
        // if is even then print the sum of 2 numbers
        for (size_t iterator = 0 ; iterator< goldbachNumber.sums.size();
        iterator++) {
          // Print the numbers that make the Goldbach sum for strong conjecture
          ostream << goldbachNumber.sums[iterator] << " + "
          << goldbachNumber.sums[iterator+1];
          ++iterator;
          if ((iterator+1) != goldbachNumber.sums.size()) {
            ostream <<" , ";
          }
        }
      } else {
        // if is odd then print the sum of 3 numbers
        for (size_t iterator = 0 ; iterator < goldbachNumber.sums.size();
         iterator++) {
          // Print the numbers that make the Goldbach sum for weak conjecture
          ostream <<goldbachNumber.sums[iterator] << " + "
          << goldbachNumber.sums[iterator+1] << " + "
          << goldbachNumber.sums[iterator+2];
          ++iterator;
          ++iterator;
          if ((iterator+1) != goldbachNumber.sums.size()) {
            ostream <<" , ";
          }
        }
      }
    }
  } else {
    ostream << "NA";
  }
  ostream << "</p>";
  // next line to the next number
  ostream <<"<br>";
  return ostream;
}

bool GoldbachNumber::operator==(const GoldbachNumber& other) const{
  bool equals = false;
  if((this->alphanumeric == other.alphanumeric) && (this->amountSums == other.amountSums) && (this->sums == other.sums) 
  && (this->validN == other.validN) && (this->number == other.number) && (this->positive == other.positive)){
    equals = true;
  }
  return equals;
}
