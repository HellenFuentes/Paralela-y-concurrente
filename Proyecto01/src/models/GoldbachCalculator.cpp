/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#include "GoldbachCalculator.hpp"
GoldbachCalculator::GoldbachCalculator() {
}

GoldbachCalculator::~GoldbachCalculator() {
}

void* GoldbachCalculator::startGoldbach(void* data) {
  // Private data for each thread
  GoldbachNumber *actual = reinterpret_cast<GoldbachNumber*>(data);
  // Vector that contains all numbers
  if (actual->validN) {
    if (actual->getEven()) {
      // if the number is even
      strongConjecture(actual);
    } else {
      // otherwise the number is odd
      weakConjecture(actual);
    }
  }
  return NULL;
}

int64_t GoldbachCalculator::primes(int64_t number) {
  bool stop = false;
  bool isPrime = true;
  if (number == 0 || number == 1) {
    // The number is not prime, the number is 0 or 1
    isPrime = false;
  }
  if (number == 4) {
    // The number is not prime, the number is 4
    isPrime = false;
  } else {
    for (int checker = 2; checker < ((number)/(2)) && (!stop) ; checker++) {
      if ((number % checker) == 0) {
        // If the number can be divided with checker and its remainder
        // is zero then the number is not prime
        stop = true;
        isPrime = false;
      }
    }
  }
  return isPrime;
}

/*sums is a variable that tell the subrutine if we are searching for 
the amount of sums.*/
void GoldbachCalculator::strongConjecture(GoldbachNumber* numberC) {
  int64_t number = numberC->getNumber();
  int64_t allsums = 0ll;
  // Variable firstN if the first Number to sum other
  for (int64_t firstN = 0; firstN <= (number/2); firstN++) {
    for (int64_t secondN =0 ; secondN <= (number); secondN++) {
      // Check if the firstN and seconN are primes
      if (primes(firstN) && primes(secondN)) {
        // if the sum of the 2 primes are equal to the number print it
        int64_t validSum = firstN + secondN;
        if (validSum == number) {
          if (numberC->getPositive()) {
            ++allsums;
          } else {
            // if we have storage space then
            // store the numbers that composed the sum
            numberC->sums.push_back(firstN);
            numberC->sums.push_back(secondN);
            ++allsums;
          }
        }
      }
    }
  }
  numberC->setAmountSums(allsums);
}

void GoldbachCalculator::weakConjecture(GoldbachNumber* numberC) {
  int64_t number = numberC->getNumber();
  int64_t allSums = 0ll;
  for (int64_t firstN = 0 ; firstN <= (number/2) ; firstN++) {
    for (int64_t secondN =firstN ; secondN<= (number/2) ; secondN++) {
      for (int64_t thirdN =secondN ; thirdN <= (number) ; thirdN++) {
        // If all current numbers are primes then verify if the sum match
        if (primes(firstN)&&primes(secondN)&&primes(thirdN)) {
          // Sum of all current numbers
          int64_t sum = firstN+secondN+thirdN;
          // If the sum match with the number
          if (sum == number) {
            if (numberC->getPositive()) {
            ++allSums;
          } else {
              // store the numbers that composed the sum
              numberC->sums.push_back(firstN);
              numberC->sums.push_back(secondN);
              numberC->sums.push_back(thirdN);
              ++allSums;
            }
          }
        }
      }
    }
  }
  numberC->setAmountSums(allSums);
}
