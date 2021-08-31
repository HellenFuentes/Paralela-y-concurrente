/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#ifndef SRC_ORACULO_HPP_
#define SRC_ORACULO_HPP_
#include <vector>
#include <string>
#include "MapaMagico.hpp"

class Oraculo {
 public:
  /**
  * @brief crea un output con el resultado de los mapas procesados
  * @details crea una carpeta llamada Salidas y almacena ahí los outputs de cada mapa
  * @param mapa quien conquiene el mapa procesado
  */
  void ecribirSalida(MapaMagico *mapa);
};

#endif  // SRC_ORACULO_HPP_
