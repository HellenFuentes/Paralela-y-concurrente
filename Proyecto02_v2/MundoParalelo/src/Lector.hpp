/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#ifndef SRC_LECTOR_HPP_
#define SRC_LECTOR_HPP_
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string>
#include "Trabajo.hpp"
class MapaMagico;

class Lector{
 public:
  /**
  * @brief lee un archivo de trabajo y obtiene los nombres de los mapas que debe de procesar el programa y sus midnights
  * @details guarda los datos en un vector de la clase Trabajo
  * @param nombreArchivo nombre del archivo de trabajo que contiene los mapas
  * @param trabajos vector de trabajo donde se guardan los nombres de los mapas y su correspondiente cantidad de midnights
  * @param ruta ruta donde se encuenta el archivo de trabajo y los mapas
  */
  void lectorTrabajo(std::string nombreArchivo,
    std::vector<Trabajo>* trabajos, std::string ruta);

  /**
  * @brief lee un archivo correspondiente a un mapa
  * @details obtiene las dimensiones del mapa y su contenido, y llena un MapaMagico en su midnight 0
  * @param nombreArchivo nombre del archivo de un mapa
  * @param mapaMagico vector de mapas mágicos donde se guardan las dimensiones del mapa y su contenido
  * @param ruta ruta donde se encuenta el archivo del mapa
  */
  void lectorMapa(std::string nombreArchivo,
    MapaMagico* mapaMagico, std::string ruta, int numThreads);
};

#endif  // SRC_LECTOR_HPP_
