/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#ifndef SRC_ESPEJOMAGICO_HPP_
#define SRC_ESPEJOMAGICO_HPP_
#include <vector>
#include "MapaMagico.hpp"
#include "VisorFuturo.hpp"

class EspejoMagico{
 private:
  MapaMagico* isla;
  int numThreads;

 public:
  /**
  * @brief constructor recibe un vector de mapas de islas
  * @details inicializa el parámetro que recibe como islas
  * @param isla el vector de mapas
  */
  explicit EspejoMagico(MapaMagico* isla, int numThreads);

  /**
  * @brief itera sobre las islas y las manda a evaluar al método evaluarIsla
  * @details evalua cada mapa mediante el método evaluarIsla();
  */
  void verDestino();

  /**
  * @brief evalua si el numero de midnights es negativo o positivo y actúa de acuerdo a ello
  * @details revisa el mapa y aplica midnights
  * @details procesa el mapa actual y guarda el resultado de el/los recorridos en el vector resultados
  * @param isla corresponde al mapa actual
  */
  void evaluarIsla(MapaMagico *isla);
};

#endif  // SRC_ESPEJOMAGICO_HPP_
