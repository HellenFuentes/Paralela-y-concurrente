#include "Mathematicians.hpp"

Mathematicians::Mathematicians(Queue<NumbersContainer>* queue,
  const NumbersContainer empty):Consumer(queue,empty){

}

int Mathematicians::run(){
  consumeForever();
  return EXIT_SUCCESS;
}

void Mathematicians::consume(const NumbersContainer& work){
  NumbersContainer myWork(work);
  calculator.startGoldbach(myWork.work);
  myWork.mutex->lock();
  *myWork.actualNumbers = *myWork.actualNumbers + 1;
  if(*myWork.actualNumbers == *myWork.totalNumbers){
    myWork.sem->signal();
  }
  myWork.mutex->unlock();
}