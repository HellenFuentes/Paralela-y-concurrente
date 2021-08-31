/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#include "Trabajo.hpp"

Trabajo::Trabajo() {
}

Trabajo::Trabajo(std::string nombreMapa, int numMidnights) {
  this->nombreMapa = nombreMapa;
  this->numMidnights = numMidnights;
}

Trabajo::~Trabajo() {
}

std::string Trabajo::getNombreMapa() {
  return this->nombreMapa;
}

int Trabajo::getNumMidnights() {
  return this->numMidnights;
}
