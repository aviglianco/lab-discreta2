#ifndef __RADIX_SORT_H__
#define __RADIX_SORT_H__

#include "APIG23.h"


/**
 * @brief Encuentra el máximo elemento en un arreglo.
 * @param arr Arreglo de enteros.
 * @param n Tamaño del arreglo.
 * @returns El máximo elemento del arreglo.
*/
u32 HallarMax(u32 *arr, int n);


/**
 * @brief el algoritmo de ordenamiento radix sort para ordenar de forma decreciente.
 * La complejidad temporal es O(n).
 * @param arr Arreglo de enteros a ordenar.
 * @param n Tamaño del arreglo.
 * @returns El arreglo ordenado en forma descendente.
*/
void RadixSort(u32 *arr, int n);

#endif