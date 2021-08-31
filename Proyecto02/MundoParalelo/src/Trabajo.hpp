/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#ifndef SRC_TRABAJO_HPP_
#define SRC_TRABAJO_HPP_
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string>

class Trabajo {
 private:
  // variables de clase privadas
  std::string nombreMapa;
  int numMidnights;

 public:
  // constructor y destructor de clase
  Trabajo();
  ~Trabajo();

  /**
  * @brief constructor de clase sobrecargado, inicializa nombreMapa = nombreMapa, numMidnights = numMidnights
  * @details se hace con el objetivo de poder obtener el nombre del mapa y número de midnights de un trabajo
  *   y guardarlo en la clase Trabajo
  * @param nombreMapa el nombre del mapa obtenido del archivo de trabajo
  * @param numMidnights el número de midnights correspondientes al mapa
  */
  Trabajo(std::string nombreMapa, int numMidnights);

  /**
  * @brief obtiene el nombre del mapa, guardado en nombreMapa en la clase trabajo, y lo retorna
  * @return nombre del mapa
  */
  std::string getNombreMapa();

  /**
  * @brief obtiene el número de midnights de un mapa, guardado en numMidnights en la clase trabajo, y lo retorna
  * @return número de midnights de un mapa
  */
  int getNumMidnights();
};

#endif  // SRC_TRABAJO_HPP_
