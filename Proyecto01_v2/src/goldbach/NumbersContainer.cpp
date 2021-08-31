#include "NumbersContainer.hpp"

NumbersContainer::NumbersContainer(const NumbersContainer& other){
  this->mutex = other.mutex;
  this->actualNumbers = other.actualNumbers;
  this->totalNumbers = other.totalNumbers;
  this->sem = other.sem;
  this->work = other.work;
}

NumbersContainer::NumbersContainer(){
  this->sem = nullptr;
  this->work = nullptr;
  this->actualNumbers = nullptr;
  this->totalNumbers = nullptr;
  this->mutex = nullptr;
}

NumbersContainer::NumbersContainer(std::mutex* mutex,int *actualNumbers,int* totalNumbers, GoldbachNumber* work, Semaphore *sem){
  this->mutex = mutex;
  this-> totalNumbers = totalNumbers;
  this->actualNumbers = actualNumbers;
  this->work = work;
  this->sem = sem;
  
}

bool NumbersContainer::operator==(const NumbersContainer& other) const{
  bool equals = false;
  if((other.work == this->work) && (other.actualNumbers == this->actualNumbers) && 
  (other.totalNumbers == this->totalNumbers) && (other.mutex == this->mutex)){
    equals = true;
  }
  return equals;
}