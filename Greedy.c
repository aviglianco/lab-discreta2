#include "APIParte2.h"
#include <stdlib.h>
#include <stdbool.h>


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