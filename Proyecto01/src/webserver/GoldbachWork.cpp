/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#include "GoldbachWork.hpp"

GoldbachWork::GoldbachWork(std::string& input,
  HttpRequest& request, HttpResponse& response):
  input(input), request(request), response(response),
  goldbachNumbersList(new GoldbachNumbersList(input)) {
}

GoldbachWork::~GoldbachWork() {
  delete this->goldbachNumbersList;
}

GoldbachNumbersList* GoldbachWork::getGoldbachNumbersList() {
  return this->goldbachNumbersList;
}
