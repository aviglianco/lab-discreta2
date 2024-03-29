#ifndef __APIP2_H
#define __APIP2_H


#include "APIG23.h"


/**
 * @brief Corre el algoritmo Greedy.
 * @param G el grafo sobre el que se quiere correr el algoritmo.
 * @param Orden el orden en el que se quiere correr el algoritmo.
 * @param Color el arreglo donde se va a guardar el coloreo.
 * @returns El número de colores usados.
*/
u32 Greedy(Grafo G,u32* Orden,u32* Color);


/**
 * @brief Ordena los indices de Color de forma que los indices de color el mayor impar,
 * luego los indices de color el segundo mayor impar, etc hasta terminar con los impares,
 * y luego pone los indices de color el mayor par, luego el segundo mayor par, etc.
 * @param n la cantidad de vertices del grafo.
 * @param Orden el arreglo donde se va a guardar el orden.
 * @param Color el arreglo con el coloreo.
 * @returns 0 en caso de éxito, 1 en caso de error.
*/
char OrdenImparPar(u32 n,u32* Orden,u32* Color);


/**
 * @brief Ordena los indices de Color de la forma especificada en la consigna.
 * @param G el grafo sobre el que se quiere correr el algoritmo.
 * @param Orden el arreglo donde se va a guardar el orden.
 * @param Color el arreglo con el coloreo.
 * @returns 0 en caso de éxito, 1 en caso de error.
*/
char OrdenJedi(Grafo G,u32* Orden,u32* Color);


#endif

