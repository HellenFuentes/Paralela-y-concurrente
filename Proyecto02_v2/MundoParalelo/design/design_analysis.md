# Universidad de Costa Rica
## Bosque Encantado Paralelo
## Segunda fase
### Versión 2.0

## Tipo de descomposición y mapeo, mediante mpi

**Descomposicion:**

Cada mapa del archivo de trabajo (job).

**Mapeo:**

El tipo de mapeo es dinamico, cada vez que un proceso termina con un trabajo pregunta al proceso principal si existe algun trabajo por realizar, si esto es correcto le asigna un trabajo, si no se envia una condicion de parada al proceso.


## Tipo de descomposición y mapeo, mediante OpenMP

**Descomposicion:**

Filas de una matriz.

**Mapeo:**

El tipo de mapeo es de tipo estático, como se conoce con anticipacion la cantidad de unidades de trabajo, entonces se elige este tipo de mapeo, además el tipo de trabajo que realiza cada trabajador similar, por lo que elegir este tipo de mapeo nos beneficia.



## Ventajas y desventajas para cada uno de los puntos anteriores

### Descomposicion y mapeo MPI

**Desventaja:**

El proceso 0, de aqui en adelante denominado principal, no puede realizar calculos, y debe estar pendiente de los trabajadores. Ya que, si alguno necesita un trabajo el debe proporcionárselo.

**Ventaja:**

Cada trabajador tiene control sobre su trabajo y la reparticion de este es mas equitativo, ya que, cuando un proceso termina un trabajo solicita otro al proceso principal, a diferencia de otros tipos de mapeo donde la distribucion de la carga no suele ser equitativa.

### Descomposicion y mapeo OpenMP

**Desventaja:**

Cuando matrices de tamaño pequeño son ingresados para ser procesados, el trabajo de sincronización de hilos ocupa mucho tiempo de ejecución y causa un overhead en el programa.

**Ventaja:**

Como mapeo estático cada hilo tiene asignado un bloque fijo en las iteraciones de los mapas y la sincronización entre los hilos es menor que con otros tipos de mapeos, además, como el trabajo a realizar es similar para cada uno de los trabajadores, este mapeo se beneficia bastante.
