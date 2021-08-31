/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#include "EspejoMagico.hpp"
#include <omp.h>

EspejoMagico::EspejoMagico(MapaMagico* isla) {
  this->isla = isla;
}

void EspejoMagico::verDestino() {
  evaluarIsla(this->isla);
}
void EspejoMagico::evaluarIsla(MapaMagico* isla) {
  // Escribe el mapa actual en el directorio Salidas
  isla->procesarMapaActual();
  VisorFuturo visor;
  // Si en la isla solo se quiere ver el resultado final
  if (isla->numeroIteraciones < 0) {
    isla->numeroIteraciones = isla->numeroIteraciones*(-1);
    for (int futuro = 0; futuro < isla->numeroIteraciones; futuro++) {
      // Manda a revisar el mapa para la siguiente midnight
      visor.revisarMapa(isla);
      if (futuro == isla->numeroIteraciones-1) {
        // SI es el ultimo mapa, lo manda a salida.
        isla->procesarMapaActual();
      }
    }
  } else {
    // Si se quiere observar todo los procedimientos paso a paso
    for (int futuro = 0; futuro < isla->numeroIteraciones; futuro++) {
      // Manda a revisar el mapa para la siguiente midnight
      visor.revisarMapa(isla);
      // Manda el mapa resultante a la salida
      isla->procesarMapaActual();
    }
  }
  // Vuelve su mapa vacio y con 0 de dimensiones
  isla->liberarMemoria();
}
