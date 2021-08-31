/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/

#include <omp.h>
#include <iostream>
#include "VisorFuturo.hpp"

VisorFuturo::VisorFuturo() { }

VisorFuturo::~VisorFuturo() { }

void VisorFuturo::revisarMapa(MapaMagico* mapa) {
  alistarCopia(mapa->mapa);
  // Repartir las filas de la matriz entre los hilos
  #pragma omp parallel for num_threads(8) shared(mapa, copia) schedule(static) collapse(2)
  for (size_t f = 0; f < mapa->mapa.size(); f++) {
    for (size_t c = 0; c < mapa->mapa[0].size(); c++) {
      evaluarReglas(f, c, mapa);
    }
  }
  ++mapa->numeroActual;
}

void VisorFuturo::evaluarReglas(int f, int c, MapaMagico* mapa) {
  if (copia[f][c] == ARBOL) {
    // Si es arbol la celda solo hay 2 reglas
    evaluarInundacion(f, c, mapa);
    evaluarHacimiento(f, c, mapa);
  } else {
    if (copia[f][c] == LAGO) {
      // Si la celda es lago
      evaluarSequia(f, c, mapa);
    } else {
      if (copia[f][c] == PRADERA) {
        // Si es pradera
        evaluarReforestacion(f, c, mapa);
      }
    }
  }
}

// ---------------------------------------------------------------REGLAS-----------------------------------------------------------

void VisorFuturo::evaluarInundacion(int f, int c, MapaMagico* mapa) {
  // Si encuentra 4 lagos aplica la regla
  if (examinarCelda(f, c, LAGO, 4)) {
    mapa->mapa[f][c]= LAGO;
  }
}

void VisorFuturo::evaluarSequia(int f, int c, MapaMagico* mapa) {
  // Si no encuentra 3 lagos aplica la regla
  if (!examinarCelda(f, c, LAGO, 3)) {
    mapa->mapa[f][c]= PRADERA;
  }
}

void VisorFuturo::evaluarReforestacion(int f, int c, MapaMagico* mapa) {
  // Si encuentra 3 arboles aplica la regla
  if (examinarCelda(f, c, ARBOL, 3)) {
    mapa->mapa[f][c]= ARBOL;
  }
}

void VisorFuturo::evaluarHacimiento(int f, int c, MapaMagico* mapa) {
  // Si encuentra 5 arboles aplica la regla
  if (examinarCelda(f, c, ARBOL, 5)) {
    mapa->mapa[f][c]= PRADERA;
  }
}

//------------------------------------------------------------------------------------------------------------------------------------

bool VisorFuturo::examinarCelda(int f, int c, char encontrar, int cuantos) {
  int encontrados = 0;
  bool parar = false;
  // Examina las 8 celdas adyacentes a la celda buscada
  for (int fila = f-1; fila <= f+1 && (!parar); fila++) {
    // Verifica que la posicion sea valida
    if (verificarPosicion(fila, 0)) {
      for (int columna = c-1; columna<= c+1 && (!parar) ; columna++) {
        // Verifica que la posicion sea valida
        if (verificarPosicion(0, columna) && (f != fila || c != columna)) {
          // SI encuentra lo que le mandaron a buscar
          if (this->copia[fila][columna] == encontrar) {
            ++encontrados;
            // SI encontro la cantidad que requieren para el ciclo
            if (encontrados == cuantos) {
              parar = true;
            }
          }
        }
      }
    }
  }
  return parar;
}

bool VisorFuturo::verificarPosicion(int f, int c) {
  bool valida = true;
  // Verifica que la fila y columna sea valida
  if ((f < 0) || (c < 0) || (c >= static_cast<int>(this->copia[0].size())) ||
    (f >= static_cast<int>(this->copia.size()))) {
    valida = false;
  }
  return valida;
}

void VisorFuturo::alistarCopia(std::vector<std::vector<char>> original) {
  // Crea una copia de la matriz original en la variable de clase copia
  copia.swap(original);
}

// Metodo de prueba para imprimir una matriz con un mensaje
void VisorFuturo::imprimirMatrizMensaje(std::string mensaje,
  std::vector<std::vector<char>> matriz) {
  std::cout << mensaje<< std::endl;
  for (size_t i= 0 ; i < matriz.size(); i++) {
    for (size_t j = 0 ; j < matriz[0].size() ; j++) {
      std::cout << matriz[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << std::endl;
}
