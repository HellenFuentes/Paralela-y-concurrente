/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
*/
#include <mpi.h>
#include <sys/stat.h>
#include "Controlador.hpp"
#include "GeneradorMagico.hpp"
#include "EspejoMagico.hpp"
#define DIRECTORIO_SALIDA "../Salidas"
#define STOP_CONDITION -3
#define INITIAL_STATE -1

Controlador::Controlador() {
  this->rutaArchivos = "";
  this->numThreads = 0;
}

Controlador::~Controlador() { }

void Controlador::iniciar(std::string nombreArchivo, std::string ruta,
int argc, char* argv[], int numThreads) {
  this->numThreads = numThreads;
  rutaArchivos = ruta;
  GeneradorMagico generador;
  //  Obtiene los mapas de un job
  generador.obtenerIslas(nombreArchivo, ruta, &this->trabajos);
  // Crea el directorio de salida si no existe
  crearDirectorio();
  // Itera sobre los Trabajos (mapas del job)
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    int my_rank = INITIAL_STATE;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    if (my_rank == 0) {
      this->repartirTrabajo();
    } else {
      this->aceptarTrabajo();
    }
    MPI_Finalize();
  }
}

void Controlador::liberarMemoria(MapaMagico *eliminar) {
  delete eliminar;
}

void Controlador::crearDirectorio() {
  mkdir(DIRECTORIO_SALIDA, 0777);
}

void Controlador::repartirTrabajo() {
  size_t trabajoRepartido = 0;

  while (trabajoRepartido < trabajos.size()) {
    int trabajador = INITIAL_STATE;

    MPI_Recv(&trabajador, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);

    MPI_Send(&trabajoRepartido, 1, MPI_INT, trabajador, 0, MPI_COMM_WORLD);
    trabajoRepartido++;
  }

  int process_count = INITIAL_STATE;
  MPI_Comm_size(MPI_COMM_WORLD, &process_count);
  int barrera = 0;

  while (barrera < (process_count - 1)) {
    int stopCondition = STOP_CONDITION;
    int trabajador = INITIAL_STATE;
    MPI_Recv(&trabajador, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    MPI_Send(&stopCondition, 1, MPI_INT, trabajador, 0, MPI_COMM_WORLD);
    ++barrera;
  }
}

void Controlador::aceptarTrabajo() {
  GeneradorMagico generador;
  int my_rank = INITIAL_STATE;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int posicionTrabajo = INITIAL_STATE;
  while (posicionTrabajo != STOP_CONDITION) {
    MPI_Send(&my_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Recv(&posicionTrabajo, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    if (posicionTrabajo != STOP_CONDITION) {
      std::cout << "proceso # " << my_rank
      << " le toco mapa #" << posicionTrabajo
                << std::endl;
      // Trabaja sobre 1 mapa del job, le da dimensiones y rellena la matriz
      MapaMagico *islaActual = generador.obtenerMapa(
      trabajos[posicionTrabajo].getNombreMapa(),
      trabajos[posicionTrabajo].getNumMidnights(),
      rutaArchivos, this->numThreads);
      // Ve el destino del mapa despues de n midnights
      EspejoMagico clarividente(islaActual, this->numThreads);
      clarividente.verDestino();
      // Libera la memoria que ocupo el mapa
      liberarMemoria(islaActual);
    }
  }
}
