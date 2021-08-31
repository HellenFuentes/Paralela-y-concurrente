/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#include "GeneradorMagico.hpp"
#include <omp.h>

GeneradorMagico::GeneradorMagico() {
  this->lector = Lector();
}

void GeneradorMagico::obtenerIslas(std::string nombreArchivo, std::string ruta,
std::vector<Trabajo>* escribir) {
  // Obtiene los mapas de un job y los escribe en lo que recibe como parametro
  lector.lectorTrabajo(nombreArchivo, escribir, ruta);
}

MapaMagico* GeneradorMagico::obtenerMapa(std::string nombreMapa,
  int midnights, std::string ruta, int numThreads) {
  // Crea un nuevo mapa, para rellenarlo con el archivo que abra
  MapaMagico *mapaMagico = new MapaMagico;
  mapaMagico->miNombre = nombreMapa;
  lector.lectorMapa(nombreMapa, mapaMagico, ruta, numThreads);
  mapaMagico->numeroIteraciones = midnights;
  // Devuelve el mapa creado
  return mapaMagico;
}
