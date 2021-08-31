/*
* Copyright 2021 Hellen Fuentes Artavia - Universidad de Costa Rica
*/
#include "distributor.hpp"
#include <omp.h>
#include <mpi.h>

#define ASKER_TAG 0

~Distributor() {
  for (size_t i =0 ; i < nums.size(); i++) {
    delete nums[i];
  }
}

void Distributor::addNum(int64_t number) {
  Number *newNumber = new Number;
  newNumber->number = number;
    nums.push_back(newNumber);
}

void Distributor::calculate(size_t thread_count) {
  for (size_t num = 0; num < nums.size(); num++) {
    goldbach->goldbach(nums.at(num), thread_count);
  }
}

void Distributor::calculateDistributed(size_t thread_count, int argc,
char *argv[]) {
  int my_id;  // Identification of each process
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    if (my_id == 0) {  // if id = 0, process will be the sender
      this->sendWork();
    } else {
      // if not, process will be a receiver
      this->receiveWork(thread_count);
    }
    MPI_Finalize();
  }
}

void Distributor::sendWork() {
  int workToDo = 0;
  int numsAmount = nums.size();
  int stop = -1;  //  stop condition
  while (workToDo < numsAmount) {
    int asker;
    MPI_Recv(&asker, 1, MPI_INT, MPI_ANY_SOURCE, ASKER_TAG,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&workToDo, 1, MPI_INT, asker, 0, MPI_COMM_WORLD);
    workToDo++;
  }
  int process_count = -1;
  MPI_Comm_size(MPI_COMM_WORLD, &process_count);
  int done = 0;
  // while there is none stop condition, keep going
  while (done < process_count - 1) {
    int asker;
    MPI_Recv(&asker, 1, MPI_INT, MPI_ANY_SOURCE, ASKER_TAG,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&stop, 1, MPI_INT, asker, 0, MPI_COMM_WORLD);
    done++;
  }
}

void Distributor::receiveWork(size_t thread_count) {
  int my_id;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
  int numsPosition = 1;
  while (numsPosition != -1) {
    MPI_Send(&my_id, 1, MPI_INT, 0, ASKER_TAG, MPI_COMM_WORLD);
    MPI_Recv(&numsPosition, 1, MPI_INT64_T, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    if (numsPosition != -1) {
      calculate(thread_count);
    }
  }
}

void Distributor::printSums(Number *numbers) {
  // prints the original number
  std::cout << numbers->number;
  printf(": ");
  // if the number is valid (-5 > number > 5)
  if (!numbers->notValid) {
    // prints the amount of sums
    std::cout << numbers->sumsAmount << " sums: ";
    // if the number is negative
    if (!numbers->positive) {
      // from the initial number until the last one added to the array
      for (size_t index = 0; index < numbers->sums.size(); index++) {
        // if the number is even
        if (numbers->even == true) {
          // print the prime numbers part its sum
          std::cout << numbers->sums[index] << " + " << numbers->sums[index+1];
          index = index + 1;
          if ((index+1)!= numbers->sums.size()) {
            printf(", ");
          }
          // if the number is odd
        } else {
          // print the prime numbers part its sum
          std::cout << numbers->sums[index] << " + "
          << numbers->sums[index+1] << " + " << numbers->sums[index+2];
          index = index + 2;
          if ((index+1)!= numbers->sums.size()) {
            printf(", ");
          }
        }
      }
    }
    // if the number is not valid (-5 < number < 5)
  } else {
    printf("NA");
  }
  printf("\n");
}

void Distributor::print() {
  for (size_t i =0 ; i < nums.size(); i++) {
       printSums(nums[i]);
  }
}
