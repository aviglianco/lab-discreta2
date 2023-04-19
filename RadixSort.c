#include <stdlib.h>
#include "RadixSort.h"


/**
 * @brief Encuentra el máximo elemento en un arreglo.
 * @param arr Arreglo de enteros.
 * @param n Tamaño del arreglo.
 * @returns El máximo elemento del arreglo.
*/
static u32 HallarMax(u32 *arr, int n) {
    u32 max = *arr;
    for (int i = 1; i < n; i++) {
        if (*(arr + i) > max) {
            max = *(arr + i);
        }
    }
    return max;
}


/**
 * @brief Aplica el algoritmo de ordenamiento por conteo basado en el dígito 
 * en la posición exp.
 * @param arr Arreglo de enteros a ordenar.
 * @param n Tamaño del arreglo.
 * @param exp Posición del dígito a ordenar.
*/
static void CountingSort(u32 *arr, int n, int exp) {
    u32 *output = malloc(n * sizeof(u32));
    int *count = calloc(10, sizeof(int));

    // Contamos el número de veces que aparece cada dígito en el arreglo.
    for (int i = 0; i < n; i++) {
        count[(*(arr + i) / exp) % 10]++;
    }

    // Modificamos count[i] para que contenga la posición real del dígito en el arreglo de salida.
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Construimos el arreglo de salida.
    for (int i = n - 1; i >= 0; i--) {
        *(output + count[(*(arr + i) / exp) % 10] - 1) = *(arr + i);
        count[(*(arr + i) / exp) % 10]--;
    }

    // Copiamos el arreglo de salida al arreglo original.
    for (int i = 0; i < n; i++) {
        *(arr + i) = *(output + i);
    }

    free(output);
    free(count);
}


// Implementación de RadixSort
void RadixSort(u32 *arr, int n) {
    int max = HallarMax(arr, n);

    // Aplicamos countingSort para cada dígito. 
    for (int exp = 1; max / exp > 0; exp *= 10) {
        CountingSort(arr, n, exp);
    }

    // Invertimos el arreglo para que quede ordenado de forma descendente.
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int temp = *(arr + i);
        *(arr + i) = *(arr + j);
        *(arr + j) = temp;
    }
}