/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#include "GoldbachWork.hpp"
#include "Socket.hpp"

GoldbachWork::GoldbachWork(std::string& input,
  HttpRequest& request, HttpResponse& response):
  input(input), request(&request), response(&response),
  goldbachNumbersList(new GoldbachNumbersList(input)) {
}
GoldbachWork::GoldbachWork(){
  this->request = nullptr;
  this->response = nullptr;
  this->input = "";
  this->goldbachNumbersList = nullptr;
}
GoldbachWork::~GoldbachWork() {
  if(goldbachNumbersList!= nullptr){
    delete this->goldbachNumbersList;
  }
}

GoldbachNumbersList* GoldbachWork::getGoldbachNumbersList() {
  return this->goldbachNumbersList;
}

bool GoldbachWork::operator==(const GoldbachWork& other) const {
  return this->request == other.request && this->response == other.response &&
  this->input == other.input;
}

GoldbachWork::GoldbachWork(const GoldbachWork& other){
  this->goldbachNumbersList = other.goldbachNumbersList;
  this->input = other.input;
  this->request = other.request;
  this->response = other.response;
}