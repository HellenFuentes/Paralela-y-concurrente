#ifndef MATHEMATICIANS_HPP
#define MATHEMATICIANS_HPP
#include "NumbersContainer.hpp"
#include "Consumer.hpp"
#include "GoldbachCalculator.hpp"

class Mathematicians : public Consumer<NumbersContainer>{
private:
GoldbachCalculator calculator;

public:
  Mathematicians(Queue<NumbersContainer>* queue,
  const NumbersContainer empty);
  /**
  * @brief consumer of work given by the client
  * @param socket as the work to be done
  */
  void consume(const NumbersContainer& listOfWork) override;

  /**
  * @brief consumes until last socket runs out
  */
  int run() override;

};
#endif  // MATHEMATICIANS_HPP