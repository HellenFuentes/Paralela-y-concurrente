/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#include <omp.h>
#include <string>
#include "Controlador.hpp"

int main(int argc, char* argv[]) {
  int estado = EXIT_SUCCESS;
  std::string nombreArchivo = "";
  std::string ruta = "";
  Controlador controlador;
  int numThreads = omp_get_max_threads();
  // debe ser igual a 3
  if (argc >= 3 && argc < 5) {
    nombreArchivo = argv[1];
    ruta = argv[2];
    if (argc == 4) {
      numThreads = strtoull(argv[3], nullptr, 10);
    }
  }
  if (ruta == "" || nombreArchivo == "") {
    estado = EXIT_FAILURE;
  } else {
    controlador.iniciar(nombreArchivo, ruta, argc, argv, numThreads);
  }
  return estado;
}
