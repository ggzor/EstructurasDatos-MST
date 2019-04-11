/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * Clase grafo que representa un grafo con una matriz cuadrada.
 * 
 * Fecha: 11/04/2019
 * 
 * Equipo:
 *   Axel Suárez Polo        201744436
 *   Marisol Huitzil Juárez  201745351
 *   Emmanuel Cortés Rosas   201764328
 *   Jafet Siliceo Luna      201759850
 * 
 */

#if !defined(_GRAFO_HPP_)
#define _GRAFO_HPP_

#include "ConjuntoDisjunto.hpp"
#include "Lista.hpp"
#include "Matriz.hpp"
#include <algorithm>

/**
 * Clase para representar una arista del grafo.
 */
struct Arista
{
  char inicio;
  char fin;
  int peso;
};

/**
 * Funcion para comparar las aristas del grafo.
 */
bool compararAristas(const Arista &arista1, const Arista &arista2)
{
  return arista1.peso < arista2.peso;
}

class Grafo
{
private:
  Matriz matriz;

public:
  Grafo(int cardinalidad) : matriz{Matriz{cardinalidad}} {}

  /**
   * Convierte una letra en su índice correspondiente.
   */
  static int obtenerIndice(char letra)
  {
    return letra - 'a';
  }

  /**
   * Obtiene la letra que representa el índice correspondiente.
   */
  static char obtenerLetra(int indice)
  {
    return (char)(indice + 'a');
  }

  /**
   * Obtiene la matriz que representa al grafo.
   */
  const Matriz &obtenerMatriz() const
  {
    return matriz;
  }

  Matriz &obtenerMatriz()
  {
    return matriz;
  }

  /**
   * Obtiene la cardinalidad del grafo.
   */
  int obtenerCardinalidad() const
  {
    return matriz.obtenerCardinalidad();
  }

  /**
   * Verifica que la letra esté en el grafo.
   */
  bool esLetraValida(char letra) const
  {
    int indice = obtenerIndice(letra);
    return 0 <= indice && indice < matriz.obtenerCardinalidad();
  }

  /**
   * Regresa true si el grafo es dirigido.
   */
  bool esDirigido() const
  {
    return !matriz.esSimetrica();
  }

  /**
   * Obtiene la lista de adyacentes a un vértice dado.
   * 
   * @param vertice la letra que representa el vértice.
  */
  Lista<char> obtenerAdyacentes(char vertice) const
  {
    Lista<char> resultado;
    int indice = obtenerIndice(vertice);

    for (int j = 0; j < matriz.obtenerCardinalidad(); j++)
    {
      if (matriz[indice][j] == 1)
      {
        resultado.insertarFinal(obtenerLetra(j));
      }
    }

    return resultado;
  }

  /**
   * Obtiene el árbol de expansión mínima ocupando el Algoritmo de Prim.
   */
  Lista<Arista> obtenerAEMPrim(char origen)
  {
    int inicio = obtenerIndice(origen), cardinalidad = matriz.obtenerCardinalidad();
    bool visitados[cardinalidad];
    Lista<Arista> arbol;

    // Inicializar arreglo de visitados
    for (int i = 0; i < cardinalidad; i++)
    {
      visitados[i] = false;
    }

    // Visitar el primer nodo
    visitados[inicio] = true;
    for (int i = 1; i < cardinalidad; i++)
    {
      Arista resultado{-1, -1, -1};

      for (int inicio = 0; inicio < cardinalidad; inicio++)
      {
        // Primer arista ya fue visitada
        if (visitados[inicio])
        {
          for (int fin = 0; fin < cardinalidad; fin++)
          {
            // Segunda arista no se ha visitado
            if (!visitados[fin])
            {
              // Si es el primero o el peso es menor, entonces reemplazar.
              if (matriz[inicio][fin] != 0 && (resultado.inicio == -1 || matriz[inicio][fin] < resultado.peso))
              {
                resultado.inicio = Grafo::obtenerLetra(inicio);
                resultado.fin = Grafo::obtenerLetra(fin);
                resultado.peso = matriz[inicio][fin];
              }
            }
          }
        }
      }

      visitados[Grafo::obtenerIndice(resultado.fin)] = true;
      arbol.insertarFinal(resultado);
    }

    return arbol;
  }

  /**
  * Obtiene el árbol de expansión mínima ocupando el Algoritmo de Kruskal.
  */
  Lista<Arista> obtenerAEMKruskal()
  {
    Lista<Arista> resultado;

    ConjuntoDisjunto arboles{obtenerCardinalidad()};
    Lista<Arista> aristas = obtenerAristasOrdenadas();

    int aristasAgregadas = 0;
    for (Arista &arista : aristas)
    {
      // Convertir las letras en índices numéricos
      int inicio = Grafo::obtenerIndice(arista.inicio);
      int fin = Grafo::obtenerIndice(arista.fin);

      // Verificar que la arista una arboles distintos
      if (arboles.obtenerConjuntoDe(inicio) != arboles.obtenerConjuntoDe(fin))
      {
        resultado.insertarFinal(arista);
        arboles.unirConjuntos(inicio, fin);

        aristasAgregadas++;
      }

      // Si ya se han recorrido todas las aristas necesarias
      if (aristasAgregadas == obtenerCardinalidad() - 1)
        break;
    }

    return resultado;
  }

  /**
   * Obtiene las aristas ordenadas ascendentemente del grafo
   */
  Lista<Arista> obtenerAristasOrdenadas() const
  {
    int cantidadAristas = obtenerCantidadAristas();
    Arista aristas[cantidadAristas];

    // Colectar todas las aristas del grafo
    int contador = 0;
    for (int inicio = 0; inicio < obtenerCardinalidad(); inicio++)
    {
      for (int fin = 0; fin < obtenerCardinalidad(); fin++)
      {
        if (matriz[inicio][fin] != 0)
        {
          aristas[contador++] = {Grafo::obtenerLetra(inicio), Grafo::obtenerLetra(fin), matriz[inicio][fin]};
        }
      }
    }

    // Ordenar el arreglo con la función de comparación entre aristas
    std::stable_sort(aristas, aristas + cantidadAristas, compararAristas);

    // Copiar resultados a una lista
    Lista<Arista> resultado;
    for (int i = 0; i < cantidadAristas; i++)
    {
      resultado.insertarFinal(aristas[i]);
    }
    return resultado;
  }

  // Obtiene la cantidad de aristas del grafo
  int obtenerCantidadAristas() const
  {
    int contador = 0;

    for (int i = 0; i < obtenerCardinalidad(); i++)
    {
      for (int j = 0; j < obtenerCardinalidad(); j++)
      {
        // Una arista tiene peso distinto de 0
        if (matriz[i][j] != 0)
        {
          contador++;
        }
      }
    }

    return contador;
  }
};

/**
 * El toString de la clase.
*/
std::ostream &operator<<(std::ostream &flujo, const Matriz &matriz)
{
  // Imprimir encabezado
  flujo << colorVertice << "   ";

  for (int i = 0; i < matriz.obtenerCardinalidad(); i++)
  {
    flujo << Grafo::obtenerLetra(i) << "  ";
  }
  flujo << terminarColor << std::endl;

  for (int i = 0; i < matriz.obtenerCardinalidad(); i++)
  {
    // Imprimir marcador de fila
    flujo << colorVertice << Grafo::obtenerLetra(i) << "  " << terminarColor;

    // Imprimir fila
    for (int j = 0; j < matriz.obtenerCardinalidad(); j++)
    {
      if (matriz[i][j] >= 1)
      {
        flujo << acentuar;
      }

      flujo << matriz[i][j] << "  " << terminarColor;
    }

    flujo << std::endl;
  }

  return flujo;
}

std::ostream &operator<<(std::ostream &flujo, const Grafo &grafo)
{
  // Imprime la matriz
  return flujo << grafo.obtenerMatriz();
}

#endif // _GRAFO_HPP_