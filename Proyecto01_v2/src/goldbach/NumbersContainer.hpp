#ifndef NUMBERSCONTAINER_HPP
#define NUMBERSCONTAINER_HPP
#include "GoldbachNumber.hpp"
#include "Semaphore.hpp"
#include <mutex>

class NumbersContainer{
  public:
  std::mutex* mutex;
  int* totalNumbers;
  int* actualNumbers;
  GoldbachNumber* work;
  Semaphore *sem;
  NumbersContainer();
  NumbersContainer(const NumbersContainer& other);
  NumbersContainer(std::mutex* mutex,int *actualNumbers,int* totalNumbers,
   GoldbachNumber* work, Semaphore *sem);
  bool operator==(const NumbersContainer& other) const;
};

#endif  // NUMBERSCONTAINER_HPP