# Plan de trabajo

Actividades: 
- Implementar una estructura para conjuntos disjuntos. [Completado]
- Implementar menú principal (Ajustar los menús ya existentes)  [Completado]
- Implementar menú de algoritmo de Prim
- Implementar menú de algoritmo de Kruskal
- Implementar el algoritmo de Prim 
- Implementar el algoritmo de Kruskal [Completado] 


## Preguntas

¿Cual es el main que hay que modificar?
> Es el que dice main.cpp, pero ese ocupa listas ligadas para representar el grafo, por lo que hay que reemplazar partes del codigo con el que dice main-referencia.cpp

¿Para qué es el conjunto disjunto?
> Es para representar los arboles distintos que se van formando con Kruskal. Tiene dos métodos principales, *obtenerConjuntoDe* que te dice a que conjunto pertenece un nodo, y *unirConjuntos* que es como unir dos árboles. De este modo, evitas los ciclos al ejecutar Kruskal. 

¿En si el menu solo tiene la opción de prim y kruskal no?
> Sí, al inicio del programa se lee la matriz desde la entrada (cin)

¿Hace falta el metodo imprimir caminos en el main?
> No, ya no es necesario.

¿Como se relacionan los costos con la matriz de adyacencia?
> La matriz de adyacencia contiene sólo los costos

¿Existe un arreglo de marcas?
>