#include "APIParte2.h"
#include <stdlib.h>
#include <stdbool.h>
#include "RadixSort.h"

#define MAX_U32 4294967295

/**
 * @brief Devuelve el color mínimo que no está en el arreglo de colores.
 * @param coloresIndexados arreglo de booleanos que indica si un color está o no.
 * @param cantDeColores cantidad de colores que hay.
 * @returns El color mínimo que no está en el arreglo.
*/
static u32 MinimoColorQueNoEsta(bool* coloresIndexados, u32 cantDeColores) {
    for (u32 i = 0; i < cantDeColores; i++) {
        if (coloresIndexados[i] == false)
            return i;
    }

    return cantDeColores;
}

/**
 * @brief Compara dos enteros de forma descendente.
 * @param a puntero a un entero.
 * @param b puntero a un entero.
 * @returns -1 si a < b, 1 si a > b, 0 si a = b.
*/
static int CmpDescendente(const void* a, const void* b) {
    return (*(u32 *)b - *(u32 *)a);
}


/**
 * @brief Corre el algoritmo Greedy.
 * @param G el grafo sobre el que se quiere correr el algoritmo.
 * @param Orden el orden en el que se quiere correr el algoritmo.
 * @param Color el arreglo donde se va a guardar el coloreo.
 * @returns El número de colores usados.
 * ! Pareciera ser de orden O(n*delta), ya que se ejecuta un for hasta n, 
 * ! y dentro se ejecutan distintos for hasta el grado (a lo sumo delta).
*/
u32 Greedy(Grafo G, u32* Orden, u32* Color) {
    u32 indiceTemp;
    u32 numeroDeColores = 0;
    u32 n = NumeroDeVertices(G);

    u32 grado = 0;
    bool* estaEnElVecino = NULL;

    for (u32 i = 0; i < n; i++) {
        Color[i] = MAX_U32;
    }
    // El primer vértice siempre se pinta de color 0.
    Color[Orden[0]] = 0;

    u32 delta = Delta(G);
    estaEnElVecino = calloc(delta, sizeof(bool));

    for (u32 i = 1; i < n; i++) {
        grado = Grado(Orden[i], G);
        // Inicializamos el array de colores de los vecinos.
        for (u32 j = 0; j < grado; j++) {
            estaEnElVecino[j] = false;
        }
        // Marcamos los colores de los vecinos.
        for (u32 j = 0; j < grado; j++) {
            indiceTemp = IndiceVecino(j, Orden[i], G);

            if (Color[indiceTemp] != MAX_U32) {
                estaEnElVecino[Color[indiceTemp]] = true;
            }
        }

        Color[Orden[i]] = MinimoColorQueNoEsta(estaEnElVecino, grado);
        // Calculamos el número de colores parcial.
        if (Color[Orden[i]] > numeroDeColores) {
            numeroDeColores = Color[Orden[i]];
        }
    }
    free(estaEnElVecino);
    /*
    numeroDeColores se calcula a partir del segundo vértice (i = 1). 
    Por lo tanto, hay que sumarle 1 (correspondiente a i = 0).
    */
    return numeroDeColores + 1;
}


/**
 * @brief Ordena los indices de Color de forma que los indices de color el mayor impar,
 * luego los indices de color el segundo mayor impar, etc hasta terminar con los impares,
 * y luego pone los indices de color el mayor par, luego el segundo mayor par, etc.
 * @param n la cantidad de vertices del grafo.
 * @param Orden el arreglo donde se va a guardar el orden.
 * @param Color el arreglo con el coloreo.
 * @returns 0 en caso de éxito, 1 en caso de error.
*/
char OrdenImparPar(u32 n, u32* Orden, u32* Color) {
    u32 i, j, temp;
    u32* impares = calloc(n, sizeof(u32));
    u32* pares = calloc(n, sizeof(u32));
    u32 impares_count = 0, pares_count = 0;

    if (impares == NULL || pares == NULL) {
        return 1;
    }

    // Separamos impares y pares
    for (i = 0; i < n; i++) {
        if (Color[i] % 2 == 1) {
            impares[impares_count++] = i;
        }
        else {
            pares[pares_count++] = i;
        }
    }

    // Ordenamos impares de mayor a menor
    RadixSort(impares, impares_count);

    // Ordenamos pares de mayor a menor
    RadixSort(pares, pares_count);

    // Combinamos impares y pares en un solo arreglo
    for (i = 0; i < impares_count; i++) {
        Orden[i] = impares[i];
    }
    for (i = 0; i < pares_count; i++) {
        Orden[impares_count + i] = pares[i];
    }

    free(impares);
    free(pares);

    return 0;
}


/**
 * @brief Ordena los indices de Color de la forma especificada en la consigna.
 * @param G el grafo sobre el que se quiere correr el algoritmo.
 * @param Orden el arreglo donde se va a guardar el orden.
 * @param Color el arreglo con el coloreo.
 * @returns 0 en caso de éxito, 1 en caso de error.
*/
char OrdenJedi(Grafo G, u32* Orden, u32* Color) {
    // ? Considerar la posibilidad de usar bucketSort (recomendación de la consigna)
    return NULL;
}