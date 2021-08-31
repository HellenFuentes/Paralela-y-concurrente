/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#ifndef SRC_VISORFUTURO_HPP_
#define SRC_VISORFUTURO_HPP_
#define LAGO 'l'
#define PRADERA '-'
#define ARBOL 'a'
#include <vector>
#include <string>
#include "MapaMagico.hpp"

class VisorFuturo {
 private:
  // matriz copia de la original
  std::vector<std::vector<char>> copia;
  int numThreads;

  /**
  * @brief evalúa las reglas correspondientes a una inundación para una celda en una posición
  * @param mapa donde se evalua una celda
  * @param f fila en posición
  * @param columna en posición
  */
  void evaluarInundacion(int f, int c, MapaMagico* mapa);

  /**
  * @brief evalúa las reglas correspondientes a una sequía para una celda en una posición
  * @param mapa donde se evalua una celda
  * @param f fila en posición
  * @param columna en posición
  */
  void evaluarSequia(int f, int c, MapaMagico* mapa);

  /**
  * @brief evalúa las reglas correspondientes a una reforestación para una celda en una posición
  * @param mapa donde se evalua una celda
  * @param f fila en posición
  * @param columna en posición
  */
  void evaluarReforestacion(int f, int c, MapaMagico* mapa);

  /**
  * @brief evalúa las reglas correspondientes a una hacimiento para una celda en una posición
  * @param mapa donde se evalua una celda
  * @param f fila en posición
  * @param columna en posición
  */
  void evaluarHacimiento(int f, int c, MapaMagico* mapa);

  /**
  * @brief examina la celda en una posición, su caracter contenido, sus 8 celdas a su alrededor y evalúa si es válida.
  * @details esto para proceder a realizar la validaciones de reglas
  * @param f fila en posción
  * @param c columna en posición
  * @param encontrar char a evaluar
  * @param cuantos 
  * @return parar = true si se cumplen las reglas de arbol, lago o pradera. false, si no
  */
  bool examinarCelda(int f, int c, char encontrar, int cuantos);

  /**
  * @brief verifica la posición de una celda para comprobar si es valida
  * @param f fila en posición
  * @param c columna en posición
  * @return true si es valida, false si no
  */
  bool verificarPosicion(int f, int c);

  /**
  * @brief se evalúa un mapa según las reglas que cumple una celda
  * @details si la celda es arbol se evalúa inundación y hacimiento, si la celda es lago
  *   se evalúa sequía, si la celda es pradera se evalúa reforestación
  * @param f cantidad de filas
  * @param c cantidad de columnas
  * @param mapa a evaluar
  */
  void evaluarReglas(int f, int c, MapaMagico* mapa);

 public:
  // constructor y destructor de clase
  VisorFuturo(int numThreads);
  ~VisorFuturo();

  /**
  * @brief crea una copia del mapa original mediante el método alistarCopia, 
  *   la guarda en MapaMagico y evalua las reglas para ese mapa
  * @details reglas de inundación, sequía, reforestación y hacimiento.
  * @param mapa mapa que se busca evaluar según las reglas
  */
  void revisarMapa(MapaMagico* mapa);

  /**
  * @brief recibe el mapa original y hace una copia del mismo, la guarda en la matriz copia definida en la clase actual
  * @param mapa el mapa original en el recorrido 0
  */
  void alistarCopia(std::vector<std::vector<char>> original);

  /**
  * @brief método de prueba para imprimir un mensaje y la matriz copia
  * @details utilizado para verificar si la matriz se está copiando correctamente
  * @param mensaje mensaje que se quiere imprimir para la prueba
  * @param matriz matriz a copiar
  */
  void imprimirMatrizMensaje(std::string mensaje,
    std::vector<std::vector<char>> matriz);
};

#endif  // SRC_VISORFUTURO_HPP_
