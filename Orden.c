#include "APIParte2.h"
#include <stdlib.h>
#include <stdbool.h>


// Estructura para guardar los indices de los vertices y su correspondiente color.
typedef struct verticeColorSt {
    u32 indice;
    u32 color;
} verticeColor;


// Estructura para guardar los indices de los vertices y sus correspondientes valores de F.
typedef struct verticeFSt {
    u32 indice;
    u32 color;
    u32 valor_f;
} verticeF;


/**
 * @brief Compara los colores de dos vértices en orden decreciente.
 * @param a puntero a la primera estructura verticeColor.
 * @param b puntero a la segunda estructura verticeColor.
 * @returns 1 si el color de b > a, -1 si el color de b < a, 0 si son iguales.
*/
static int verticeColorComp(const void *a, const void *b) {
    const verticeColor *ia = (const verticeColor *)a;
    const verticeColor *ib = (const verticeColor *)b;
    return (ib->color - ia->color);
}


/**
 * @brief Compara los valores de F de dos vértices en orden decreciente.
 * @param a puntero a la primera estructura verticeF.
 * @param b puntero a la segunda estructura verticeF.
 * @returns 1 si el color de b > a, -1 si el color de b < a, 0 si son iguales.
 * En el caso de que los valores de F sean iguales, se compara el color de los vértices.
 * Esto permite colocar juntos todos los vértices del mismo color, manteniendo el orden
 * por bloques.
*/
static int verticeFComp(const void *a, const void *b) {
    const verticeF *ia = (const verticeF *)a;
    const verticeF *ib = (const verticeF *)b;   
    if (ia->valor_f == ib->valor_f) {
        return(ib->color - ia->color);
    } else {
        return (ib->valor_f - ia->valor_f);
    }
}

/**
 * @brief Encuentra el máximo elemento en un arreglo.
 * @param arr Arreglo de enteros.
 * @param n Tamaño del arreglo.
 * @returns El máximo elemento del arreglo.
*/
static u32 HallarMax(u32 *arr, int n) {
    u32 max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
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
    u32 i;
    verticeColor *impares = calloc(n, sizeof(verticeColor));
    verticeColor *pares = calloc(n, sizeof(verticeColor));
    u32 impares_count = 0, pares_count = 0;

    if (impares == NULL || pares == NULL) {
        // Error al reservar memoria
        return 1;
    }

    // Separamos impares y pares
    for (i = 0; i < n; i++) {
        if (Color[i] % 2 == 1) {
            impares[impares_count].indice = i;
            impares[impares_count].color = Color[i];
            impares_count++;
        }
        else {
            pares[pares_count].indice = i;
            pares[pares_count].color = Color[i];
            pares_count++;
        }
    }

    // Ordenamos impares de mayor a menor
    qsort(impares, impares_count, sizeof(verticeColor), verticeColorComp);

    // Ordenamos pares de mayor a menor
    qsort(pares, pares_count, sizeof(verticeColor), verticeColorComp);

    // Combinamos impares y pares en un solo arreglo
    for (i = 0; i < impares_count; i++) {
        Orden[i] = impares[i].indice;
    }
    for (i = 0; i < pares_count; i++) {
        Orden[impares_count + i] = pares[i].indice;
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
    u32 n = NumeroDeVertices(G);
    u32 maxColor = HallarMax(Color, n);
    u32 *sumatoriaParcial = calloc(maxColor+1, sizeof(u32));
    verticeF *aux = calloc(n, sizeof(verticeF));

    if (sumatoriaParcial == NULL || aux == NULL) {
        // Error al reservar memoria
        return 1;
    }
    
    // Calculamos la sumatoria parcial de los grados de cada color.
    for (u32 i = 0; i < n; i++) {
        sumatoriaParcial[Color[i]] += Grado(i, G);
    }

    // Calculamos el valor final de F para cada color.
    for (u32 i = 0; i <= maxColor; i++) {
        sumatoriaParcial[i] *= i;
    }

    // Calculamos el valor de F para cada vértice.
    for (u32 i = 0; i < n; i++) {
        aux[i].indice = i;
        aux[i].valor_f = sumatoriaParcial[Color[i]];
        aux[i].color = Color[i];
    }

    // Ordenamos los vértices de mayor a menor según su valor de F.
    qsort(aux, n, sizeof(verticeF), verticeFComp);

    // Guardamos el orden en el arreglo Orden.
    for (u32 i = 0; i < n; i++) {
        Orden[i] = aux[i].indice;
    }

    free(sumatoriaParcial);
    free(aux);

    return 0;
}