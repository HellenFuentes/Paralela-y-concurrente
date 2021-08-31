/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#ifndef SRC_CONTROLADOR_HPP_
#define SRC_CONTROLADOR_HPP_
#include <vector>
#include <string>
#include "MapaMagico.hpp"
#include "Trabajo.hpp"

class Controlador {
 private:
std::vector<Trabajo> trabajos;

 public:
  // constructor y destructor
  Controlador();
  ~Controlador();

  /**
  * @brief inicia el programa de mundo encantado serial
  * @details recibe el nombre del archivo y la ruta para tener acceso al directorio donde se encuentran los mapas del trabajo
  * @param nombreArchivo el nombre del archivo de trabajo
  * @param ruta la ruta donde se encuentra el archivo de trabajo y los mapas
  */
  void iniciar(std::string nombreArchivo, std::string ruta);

  /**
  * @brief libera la memoria alojada para la creación de las islas
  * @details se hace un delete para todas las islas creadas
  * @param eliminar como el mapa que se desea liberar
  */
  void liberarMemoria(MapaMagico *eliminar);

  /**
  * @brief crea un directorio para guadar los outputs que se obtienen después de procesar uno o varios mapas
  */
  void crearDirectorio();
};

#endif  // SRC_CONTROLADOR_HPP_
