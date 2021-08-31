/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#include <sstream>
#include <string>
#include "GoldbachNumbersList.hpp"


GoldbachNumbersList::GoldbachNumbersList(std::string& input) {
  std::stringstream inputStream(input);
  std::string alphanumeric;
  while (std::getline(inputStream, alphanumeric, ',')) {
    inputs.push_back(new GoldbachNumber(alphanumeric));
  }
}

GoldbachNumbersList::~GoldbachNumbersList() {
  for (auto i : inputs) {
    delete i;
  }
}

int64_t GoldbachNumbersList::getListSize() {
  return inputs.size();
}

GoldbachNumber* GoldbachNumbersList::getGoldbachNumber(int64_t index) {
  return inputs[index];
}
std::ostream& operator << (std::ostream& ostream,
const GoldbachNumbersList& goldbachNumbersList) {
  ostream<<
  "  <style>body {font-family: monospace} h1 {color: #900C3F}</style>\n";
  for (auto goldbachNumber : goldbachNumbersList.inputs) {
    ostream << *goldbachNumber << std::endl;
  }

  return ostream;
}
