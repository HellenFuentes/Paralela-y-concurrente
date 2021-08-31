/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#ifndef SRC_MODELS_GOLDBACHNUMBERSLIST_HPP_
#define SRC_MODELS_GOLDBACHNUMBERSLIST_HPP_
#include <string>
#include <vector>
#include <iostream>
#include "GoldbachNumber.hpp"

class GoldbachNumbersList {
 public:
    /**
    * @brief constructor of GoldbachNumbersList
    * @param input as the string the numbers to which the guess is going to be made
    */
    explicit GoldbachNumbersList(std::string& input);

    // Class destructor
    ~GoldbachNumbersList();

    /**
    * @brief returns the size of the list
    * @return inputs.size() as the size of the number list
    */
    int64_t getListSize();
    /**
    * @brief returns the actual index of the list
    * @param index as the initial index
    * @return inputs[index] as the indexs of the list
    */
    GoldbachNumber* getGoldbachNumber(int64_t index);

 private:
    /**
    * @brief Vector of numbers entered by the user
    */
    std::vector<GoldbachNumber*> inputs;

    friend std::ostream& operator << (std::ostream& ostream,
    const GoldbachNumbersList& goldbachNumbersList);
};

#endif  // SRC_MODELS_GOLDBACHNUMBERSLIST_HPP_
