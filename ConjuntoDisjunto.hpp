/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * Estructura que representa múltiples conjuntos disjuntos. Esta estructura es ideal
 * para representar los distintos árboles del algoritmo de Kruskal.
 * 
 * Fecha: 04/04/2019
 * 
 * Equipo:
 *   Axel Suárez Polo        201744436
 *   Marisol Huitzil Juárez  201745351
 *   Emmanuel Cortés Rosas   201764328
 *   Jafet Siliceo Luna      201759850
 */ 
#if !defined(_CONJUNTO_DISJUNTO_HPP_)
#define _CONJUNTO_DISJUNTO_HPP_

class ConjuntoDisjunto {
  private:
  int *padres;

  public:
  /**
   * Constructor principal de la clase
   */
  ConjuntoDisjunto(int medida) : padres{new int[medida]} {
    for (int i = 0; i < medida; i++) {
      padres[i] = -1;
    }
  }

  /**
   * Obtiene cuál es el conjunto al que pertenece el parámetro.
   */
  int obtenerConjuntoDe(int nodo) {
    // Si el nodo no tiene padre, entonces es la ráiz
    if (padres[nodo] == -1) {
      return nodo;
    } else {
      // Buscar la raíz de su padre
      return obtenerConjuntoDe(padres[nodo]);
    }
  }

  /**
   * Une los conjuntos correspondientes a cada uno de los nodos.
   */
  void unirConjuntos(int nodo1, int nodo2) {
    int padre1 = obtenerConjuntoDe(nodo1);
    int padre2 = obtenerConjuntoDe(nodo2);

    // Actualizar el padre de uno de los nodos.
    padres[padre1] = padre2;
  }
};

#endif // _CONJUNTO_DISJUNTO_HPP_
