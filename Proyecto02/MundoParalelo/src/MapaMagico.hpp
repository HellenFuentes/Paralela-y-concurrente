/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#ifndef SRC_MAPAMAGICO_HPP_
#define SRC_MAPAMAGICO_HPP_
#define SALTO_LINEA 'n'
#include <vector>
#include <string>

class MapaMagico {
 public:
  // varibles publicas
  int numeroIteraciones;
  int numeroActual;
  std::string miNombre;
  // matriz
  std::vector<std::vector<char>> mapa;
  // contructor de clase
  MapaMagico();

  /**
  * @brief constructor sobrecargado que recibe el tamaño del mapa y lo establece en el setter setTamanioMapa
  * @details inicializa el tamano de la matriz en 0 y cambia su tamaño según los parámetros recibidos
  * @param f cantidad de filas
  * @param c cantidad de columnas
  */
  MapaMagico(int f, int c);

  /**
  * @brief se asigna el tamaño de la matriz (mapa) deacuerdo a las dimensiones del mapa leído
  * @details hace un resize según las dimensiones que se establecen en la primera fila del mapa
  * @param f cantidad de filas
  * @param c cantidad de columnas
  */
  void setTamanioMapa(int f, int c);

  /**
  * @brief obtiene los caracteres leidos del archivo de texto del mapa y los asigna a cada celda de la matriz
  * @param caracter caracter recibido
  */
  void rellenarCaracter(char caracter);

  /**
  * @brief procesa la matiz actual iniciando desde el recorrido 0
  * @details guarda el resultado en un vector de string para facilitar 
  *   la impresión del resultado del mapa despues de un recorrido
  */
  void procesarMapaActual();

  /**
  * @brief sobrecarga de operador, cuando se iguala un MapaMagico con otro,
  *   el otro obtiene todos los valores del MapaMagico inicial
  * @details los valores se refieren al nombre, número actual de recorido,
  *   el número de iteraciones y el resultado final
  * @param otro se refiere al mapa con el que se va a igualar un mapa
  * @return this retorna la referencia al mapa que se iguala
  */
  MapaMagico& operator = (const MapaMagico &otro);

  /**
  * @brief libera la memoria alojada para la creación de las islas
  * @details se hace un delete para todos los mapas creados
  */
  void liberarMemoria();
};

#endif  // SRC_MAPAMAGICO_HPP_
