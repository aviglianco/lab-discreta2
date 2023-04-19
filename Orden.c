#include "APIParte2.h"
#include <stdlib.h>
#include <stdbool.h>
#include "RadixSort.h"


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
    u32 i;
    u32 *impares = calloc(n, sizeof(u32));
    u32 *pares = calloc(n, sizeof(u32));
    u32 impares_count = 0, pares_count = 0;

    if (impares == NULL || pares == NULL) {
        // Error al reservar memoria
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
    return 0;
}