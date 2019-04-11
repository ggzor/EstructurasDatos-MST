/**
 * Benemérita Universidad Autónoma de Puebla
 * Estructuras de datos
 * 
 * Implementación de la interfaz para mostrar algoritmo de 
 * Prim y Kruskal.
 * 
 * Fecha: 04/04/2019
 * 
 * Equipo:
 *   Axel Suárez Polo        201744436
 *   Marisol Huitzil Juárez  201745351
 *   Emmanuel Cortés Rosas   201764328
 *   Jafet Siliceo Luna      201759850
 * 
 */
#include "Color.hpp"
#include "Grafo.hpp"
#include "Utilerias.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main();

// Lectura del grafo
Grafo leerGrafo()
{
  int cardinalidad;
  std::cout << "¿Cuántos vértices tiene el grafo? ";
  std::cin >> cardinalidad;

  if (cardinalidad <= 0)
  {
    std::cerr << "La cardinalidad no puede ser negativa.\n"
              << std::endl;

    // Reiniciar el programa
    main();
  }

  // Construir grafo con la cardinalidad dada.
  Grafo grafo{cardinalidad};

  // Obtener un apuntador a la matriz del grafo.
  Matriz &matriz = grafo.obtenerMatriz();

  std::cout << "Introduzca la matriz: " << std::endl;
  for (int y = 0; y < cardinalidad; y++)
  {
    for (int x = 0; x < cardinalidad; x++)
    {
      std::cin >> matriz[y][x];
    }
  }

  return grafo;
}

/**
 * Imprime los datos de un grafo de manera organizada.
 */
void imprimirDatosGrafo(const Grafo &grafo)
{
  std::cout << "Grafo: " << std::endl;
  std::cout << grafo << std::endl;
  std::cout << "La cardinalidad del grafo es: " << grafo.obtenerCardinalidad() << std::endl;
  std::cout << "Tipo de grafo: ";

  if (grafo.esDirigido())
    std::cout << colorVertice << "Dirigido" << terminarColor;
  else
    std::cout << "No dirigido";
  std::cout << std::endl
            << std::endl;
}

//MAIN
int main()
{
  Grafo grafo = leerGrafo();

  int op;
  do
  {
    limpiarTerminal();
    imprimirDatosGrafo(grafo);
    std::cout << "Menú:\n"
              << "  1. Aplicar algoritmo de Prim.\n"
              << "  2. Aplicar algoritmo de Kruskal.\n"
              << "  3. Salir.\n";
    std::cout << "Opción: ";
    std::cin >> op;
    std::cout << std::endl;
    
    switch (op)
    {
    case 1:
      // Lectura del vértice de origen para aplicar Prim
      char origen;
      std::cout << "Origen: " << colorVertice;
      std::cin >> origen;
      std::cout << terminarColor;

      if (grafo.esLetraValida(origen))
      {
        Lista<Arista> recorrido = grafo.obtenerAEMPrim(origen);
        std::cout <<"El árbol de expansión mínima esta conformado por las aristas: " << std::endl;
        for (Arista& arista : recorrido)
        {
          std::cout << colorVertice << arista.inicio << terminarColor 
                    << enNegritas << " -> "
                    << colorVertice << arista.fin << terminarColor
                    << ' ' << '(' << acentuar << arista.peso << terminarColor << ')'
                    << std::endl;
        }
        esperarEnter();
      }
      else
      {
        std::cout << acentuar << "El vértice dado no está en el grafo." << terminarColor << std::endl;
        esperarEnter();
      }
      break;

    case 2: {
      // Árbol de expansión mínima con Kruskal
      Lista<Arista> recorrido = grafo.obtenerAEMKruskal();
      std::cout << "El árbol de expansión mínima está conformado por las aristas: " << std::endl;
      for(Arista& arista : recorrido)
      {
        std::cout << colorVertice << arista.inicio << terminarColor 
                  << enNegritas << " -> "
                  << colorVertice << arista.fin << terminarColor
                  << ' ' << '(' << acentuar << arista.peso << terminarColor << ')'
                  << std::endl;
      }
      
      esperarEnter();
      break;
    }
    case 3:
      // Para evitar el siguiente mensaje
      break;

    default:
      std::cout << acentuar << "Opcion inválida." << terminarColor << std::endl;
      esperarEnter();
      break;
    }
  } while (op != 3);
  return 0;
}