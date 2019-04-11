/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * Clase matriz que representa los datos de un grafo y puede proporcionar
 * información sobre esta. La matriz es cuadrada.
 * 
 * Fecha: 28/02/2019
 * 
 * Equipo:
 *   Axel Suárez Polo        201744436
 *   Marisol Huitzil Juárez  201745351
 *   Emmanuel Cortés Rosas   201764328
 *   Jafet Siliceo Luna      201759850
 * 
 */

#ifndef _MATRIZ_HPP_
#define _MATRIZ_HPP_

#include "Color.hpp"
#include <ostream>

class Matriz
{
public:
  /**
   * Constructor principal.
   * 
   * @param _cardinalidad la cardinalidad de la matriz.
   */
  Matriz(int _cardinalidad)
  {
    cardinalidad = _cardinalidad;

    // Reservar memoria para las filas de la matriz.
    datos = new int *[cardinalidad];

    // Reservar memoria para todas las columnas de cada una de las filas de la matriz.
    for (int i = 0; i < cardinalidad; i++)
      datos[i] = new int[cardinalidad];
  }

  /**
   * Destructor de la clase.
   */
  ~Matriz()
  {
    for (int i = 0; i < cardinalidad; i++)
    {
      delete[] datos[i];
    }

    delete[] datos;
  }

  /**
   * Constructor por copiado.
   */
  Matriz(const Matriz &matriz) : Matriz(matriz.cardinalidad)
  {
    for (int i = 0; i < cardinalidad; i++)
    {
      for (int j = 0; j < cardinalidad; j++)
      {
        datos[i][j] = matriz[i][j];
      }
    }
  }

  /**
   * Asignación por copiado.
   */
  Matriz &operator=(const Matriz &matriz)
  {
    cardinalidad = matriz.cardinalidad;

    // Reservar memoria para las filas de la matriz.
    datos = new int *[cardinalidad];

    // Reservar memoria para todas las columnas de cada una de las filas de la matriz.
    for (int i = 0; i < cardinalidad; i++)
      datos[i] = new int[cardinalidad];

    for (int i = 0; i < cardinalidad; i++)
    {
      for (int j = 0; j < cardinalidad; j++)
      {
        datos[i][j] = matriz[i][j];
      }
    }

    return *this;
  }

  /**
   * Construcción por movimiento.
   */
  Matriz(Matriz &&matriz) : cardinalidad{matriz.cardinalidad}, datos{matriz.datos}
  {
    matriz.cardinalidad = 0;
    matriz.datos = nullptr;
  }

  /**
   * Asignación por movimiento.
   */
  Matriz &operator=(Matriz &&matriz)
  {
    cardinalidad = matriz.cardinalidad;
    datos = matriz.datos;

    matriz.cardinalidad = 0;
    matriz.datos = nullptr;

    return *this;
  }

  /**
   * Operador para indizar como si fuera un arreglo bidimensional.
   * 
   * @param fila la fila a la que se quiere acceder
  */
  const int *operator[](int fila) const
  {
    return datos[fila];
  }

  int *operator[](int fila)
  {
    return datos[fila];
  }

  /**
   * Operador para multiplicar matrices.
   * 
   * @param otra 
   */
  Matriz operator*(const Matriz &otra) const
  {
    Matriz nueva{cardinalidad};

    for (int i = 0; i < cardinalidad; i++)
    {
      for (int j = 0; j < cardinalidad; j++)
      {
        for (int k = 0; k < cardinalidad; k++)
        {
          nueva[i][j] += datos[i][k] * otra[k][j];
        }
      }
    }

    return nueva;
  }

  int obtenerCardinalidad() const
  {
    return cardinalidad;
  }

  /**
   * Determina si la matriz es simétrica.
   */
  bool esSimetrica() const
  {
    for (int i = 0; i < cardinalidad; i++)
    {
      for (int j = i + 1; j < cardinalidad; j++)
      {
        if (datos[i][j] != datos[j][i])
        {
          return false;
        }
      }
    }
    return true;
  }

private:
  int **datos;
  int cardinalidad;
};
#endif