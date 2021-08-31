/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#ifndef SRC_GENERADORMAGICO_HPP_
#define SRC_GENERADORMAGICO_HPP_
#include <vector>
#include <string>
#include "Trabajo.hpp"
#include "MapaMagico.hpp"
#include "Lector.hpp"

class GeneradorMagico {
 private:
  MapaMagico *procesar;
  Lector lector;

 public:
  // constructor y destructor de clase
  GeneradorMagico();
  ~GeneradorMagico() { }

  /**
  * @brief lee el archivo y la ruta del mismo, y lo asigna al vector de Trabajo.
  * @details para cada mapa del trabajo, obtiene el nombre del archivo y el número de midnights 
  *   y crea un nuevo mapa magico (matriz) con los resultados obtenidos
  * @param nombreArchivo el nombre del trabajo a procesar
  * @param ruta la ruta del directorio que contiene el archivo de trabajo y los mapas
  */
  void obtenerIslas(std::string nombreArchivo, std::string ruta,
    std::vector<Trabajo>* escribir);

  /**
  * @brief lee el archivo y la ruta del mismo y lo asigna a un mapaMagico
  * @details para un mapa, obtiene el nombre del archivo y el número de midnights 
  *   y lo guarda en un nuevo mapa magico (matriz)
  * @param nombreArchivo el nombre del mapa a procesar
  * @param ruta la ruta del directorio que contiene el mapa
  * @return mapaMagico creados
  */
  MapaMagico* obtenerMapa(std::string nombreMapa,
    int midnights, std::string ruta);
};

#endif  // SRC_GENERADORMAGICO_HPP_
